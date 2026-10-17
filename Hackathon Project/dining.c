/*
 * Dining Philosophers Deadlock Prevention System
 * ----------------------------------------------
 * Simulates N philosophers (pthreads) sharing N forks (pthread mutexes) and
 * compares several synchronization strategies:
 *
 *   naive       - everyone grabs left then right  (DEADLOCKS on purpose)
 *   hierarchy   - always take the lower-numbered fork first (breaks circular wait)
 *   waiter      - counting semaphore lets at most N-1 philosophers try (breaks hold & wait cycle)
 *   monitor     - mutex + condition variables, take both forks atomically (breaks hold & wait)
 *   asymmetric  - even ids pick left first, odd ids pick right first (breaks symmetry)
 *
 * Features: live ANSI terminal visualization, watchdog deadlock detector,
 * starvation/fairness metrics, and a compare mode that runs every strategy.
 *
 * Build:  make            Run:  ./dining -h
 */
#define _GNU_SOURCE
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdatomic.h>
#include <sys/wait.h>

#define MAX_PHIL 64

typedef enum { NAIVE, HIERARCHY, WAITER, MONITOR, ASYMMETRIC, NSTRAT } Strategy;
static const char *strat_name[NSTRAT] = { "naive", "hierarchy", "waiter", "monitor", "asymmetric" };
static const char *strat_desc[NSTRAT] = {
    "left then right (deadlock-prone)",
    "resource ordering (no circular wait)",
    "semaphore, max N-1 at table",
    "monitor + condition variables",
    "even/odd pick opposite fork first"
};

typedef enum { THINKING, HUNGRY, EATING } PState;

typedef struct {
    int n;               /* number of philosophers */
    Strategy strat;
    int duration;        /* seconds to run */
    int think_max_ms;
    int eat_max_ms;
    int naive_delay_ms;  /* pause between 1st and 2nd fork in naive (makes deadlock reproducible) */
    int timeout_s;       /* no-progress time before declaring deadlock */
    int visual;
} Config;

typedef struct {
    int deadlock;
    double elapsed;
    long total_meals;
    double throughput, avg_wait_ms, max_wait_ms, fairness;
} Result;

static Config cfg;

/* ---- shared simulation state (bookkeeping only; guarded by state_lock) ---- */
static pthread_mutex_t state_lock = PTHREAD_MUTEX_INITIALIZER;
static PState state[MAX_PHIL];
static int fork_owner[MAX_PHIL];            /* -1 = free */
static long meals[MAX_PHIL];
static long long wait_total_ns[MAX_PHIL], wait_max_ns[MAX_PHIL];

/* ---- synchronization objects used by the strategies ---- */
static pthread_mutex_t forks[MAX_PHIL];
static sem_t room;                          /* waiter strategy */
static pthread_mutex_t mon_lock;            /* monitor strategy */
static pthread_cond_t mon_cv[MAX_PHIL];
static PState mon_state[MAX_PHIL];

static volatile int running;
static volatile int render_stop;
static volatile int deadlock_flag;
static _Atomic long long last_progress;
static long long start_ns;

static long long now_ns(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

static void sleep_ms(int ms) {
    if (ms <= 0) return;
    struct timespec ts = { ms / 1000, (long)(ms % 1000) * 1000000L };
    nanosleep(&ts, NULL);
}

static void set_state(int id, PState s) {
    pthread_mutex_lock(&state_lock);
    state[id] = s;
    pthread_mutex_unlock(&state_lock);
}

static void set_fork(int f, int owner) {
    pthread_mutex_lock(&state_lock);
    fork_owner[f] = owner;
    pthread_mutex_unlock(&state_lock);
}

/* Lock a fork and record ownership for the visualization. */
static void lock_fork(int f, int id)  { pthread_mutex_lock(&forks[f]); set_fork(f, id); }
static void unlock_fork(int f)        { set_fork(f, -1); pthread_mutex_unlock(&forks[f]); }

/* ---------------------------------------------------------------- monitor */
static void mon_test(int i) {
    int n = cfg.n, l = (i + n - 1) % n, r = (i + 1) % n;
    if (mon_state[i] == HUNGRY && mon_state[l] != EATING && mon_state[r] != EATING) {
        mon_state[i] = EATING;
        set_fork(i, i);
        set_fork((i + 1) % n, i);
        pthread_cond_signal(&mon_cv[i]);
    }
}

static void monitor_pickup(int i) {
    pthread_mutex_lock(&mon_lock);
    mon_state[i] = HUNGRY;
    mon_test(i);
    while (mon_state[i] != EATING)
        pthread_cond_wait(&mon_cv[i], &mon_lock);
    pthread_mutex_unlock(&mon_lock);
}

static void monitor_putdown(int i) {
    int n = cfg.n, l = (i + n - 1) % n, r = (i + 1) % n;
    pthread_mutex_lock(&mon_lock);
    mon_state[i] = THINKING;
    set_fork(i, -1);
    set_fork((i + 1) % n, -1);
    mon_test(l);
    mon_test(r);
    pthread_mutex_unlock(&mon_lock);
}

/* ------------------------------------------------------ strategy dispatch */
static void acquire_forks(int id) {
    int n = cfg.n, l = id, r = (id + 1) % n;
    switch (cfg.strat) {
    case NAIVE:
        lock_fork(l, id);
        sleep_ms(cfg.naive_delay_ms);   /* everyone now holds their left fork -> deadlock */
        lock_fork(r, id);
        break;
    case HIERARCHY: {
        int first = l < r ? l : r, second = l < r ? r : l;
        lock_fork(first, id);
        lock_fork(second, id);
        break;
    }
    case WAITER:
        sem_wait(&room);
        lock_fork(l, id);
        lock_fork(r, id);
        break;
    case MONITOR:
        monitor_pickup(id);
        break;
    case ASYMMETRIC:
        if (id % 2 == 0) { lock_fork(l, id); lock_fork(r, id); }
        else             { lock_fork(r, id); lock_fork(l, id); }
        break;
    default: break;
    }
}

static void release_forks(int id) {
    int n = cfg.n, l = id, r = (id + 1) % n;
    switch (cfg.strat) {
    case MONITOR:
        monitor_putdown(id);
        break;
    case WAITER:
        unlock_fork(l);
        unlock_fork(r);
        sem_post(&room);
        break;
    default:
        unlock_fork(l);
        unlock_fork(r);
        break;
    }
}

/* ------------------------------------------------------------ philosopher */
static void *philosopher(void *arg) {
    int id = (int)(long)arg;
    unsigned seed = (unsigned)(now_ns() ^ ((long long)(id + 1) * 2654435761u));
    int first = 1;

    while (running) {
        set_state(id, THINKING);
        /* Everyone starts hungry at t=0 (worst case), which makes the naive deadlock reproducible. */
        if (!first) sleep_ms(1 + rand_r(&seed) % cfg.think_max_ms);
        first = 0;
        if (!running) break;

        set_state(id, HUNGRY);
        long long t0 = now_ns();
        acquire_forks(id);
        long long waited = now_ns() - t0;

        set_state(id, EATING);
        atomic_store(&last_progress, now_ns());
        pthread_mutex_lock(&state_lock);
        meals[id]++;
        wait_total_ns[id] += waited;
        if (waited > wait_max_ns[id]) wait_max_ns[id] = waited;
        pthread_mutex_unlock(&state_lock);

        sleep_ms(1 + rand_r(&seed) % cfg.eat_max_ms);
        release_forks(id);
    }
    set_state(id, THINKING);
    return NULL;
}

/* ---------------------------------------------------------- visualization */
#define C_RESET  "\033[0m"
#define C_BLUE   "\033[34m"
#define C_YELLOW "\033[33m"
#define C_GREEN  "\033[32m"
#define C_RED    "\033[1;31m"
#define C_BOLD   "\033[1m"

static void render(void) {
    PState st[MAX_PHIL];
    int fo[MAX_PHIL];
    long ml[MAX_PHIL];
    long long wm[MAX_PHIL];
    int n = cfg.n;

    pthread_mutex_lock(&state_lock);
    memcpy(st, state, sizeof st);
    memcpy(fo, fork_owner, sizeof fo);
    memcpy(ml, meals, sizeof ml);
    memcpy(wm, wait_max_ns, sizeof wm);
    pthread_mutex_unlock(&state_lock);

    double el = (now_ns() - start_ns) / 1e9;
    printf("\033[H\033[J");
    printf(C_BOLD "DINING PHILOSOPHERS" C_RESET "  strategy: " C_BOLD "%s" C_RESET " (%s)\n",
           strat_name[cfg.strat], strat_desc[cfg.strat]);
    printf("philosophers: %d   elapsed: %.1fs / %ds\n", n, el, cfg.duration);
    if (deadlock_flag) printf(C_RED ">>> DEADLOCK DETECTED: no progress for %ds <<<" C_RESET "\n", cfg.timeout_s);
    else               printf("status: running\n");
    printf("\n  ID  STATE      FORKS(L R)  MEALS  MAX-WAIT\n");
    printf("  --  ---------  ----------  -----  --------\n");
    for (int i = 0; i < n; i++) {
        const char *col = st[i] == EATING ? C_GREEN : st[i] == HUNGRY ? C_YELLOW : C_BLUE;
        const char *nm  = st[i] == EATING ? "EATING   " : st[i] == HUNGRY ? "HUNGRY   " : "THINKING ";
        int hl = fo[i] == i, hr = fo[(i + 1) % n] == i;
        printf("  %2d  %s%s" C_RESET "  %s %s         %5ld  %6.0fms\n", i, col, nm,
               hl ? "L" : "-", hr ? "R" : "-", ml[i], wm[i] / 1e6);
    }
    printf("\n  " C_BLUE "THINKING" C_RESET "  " C_YELLOW "HUNGRY" C_RESET "  " C_GREEN "EATING" C_RESET
           "      L/R = left/right fork held\n");
    fflush(stdout);
}

static void *renderer(void *arg) {
    (void)arg;
    while (!render_stop) { render(); sleep_ms(100); }
    return NULL;
}

/* ---------------------------------------------------------------- metrics */
static Result compute_result(double elapsed) {
    Result r = {0};
    double sum = 0, sumsq = 0;
    long long wt = 0, wmax = 0;
    pthread_mutex_lock(&state_lock);
    for (int i = 0; i < cfg.n; i++) {
        r.total_meals += meals[i];
        sum += meals[i];
        sumsq += (double)meals[i] * meals[i];
        wt += wait_total_ns[i];
        if (wait_max_ns[i] > wmax) wmax = wait_max_ns[i];
    }
    pthread_mutex_unlock(&state_lock);
    r.deadlock = deadlock_flag;
    r.elapsed = elapsed;
    r.throughput = elapsed > 0 ? r.total_meals / elapsed : 0;
    r.avg_wait_ms = r.total_meals ? wt / 1e6 / r.total_meals : 0;
    r.max_wait_ms = wmax / 1e6;
    r.fairness = sumsq > 0 ? (sum * sum) / (cfg.n * sumsq) : 0;   /* Jain's fairness index */
    return r;
}

static void print_summary(const Result *r) {
    printf("\n" C_BOLD "=== SUMMARY ===" C_RESET "\n");
    printf("Strategy   : %s\n", strat_name[cfg.strat]);
    if (r->deadlock) printf("Result     : " C_RED "DEADLOCK" C_RESET " detected after %.1fs\n", r->elapsed);
    else             printf("Result     : no deadlock in %.1fs\n", r->elapsed);
    printf("Meals      : %ld total (%.1f/s)\n", r->total_meals, r->throughput);
    printf("Wait time  : avg %.1f ms, max %.1f ms\n", r->avg_wait_ms, r->max_wait_ms);
    printf("Fairness   : %.3f (Jain's index, 1.0 = perfectly fair)\n", r->fairness);
    printf("\n  ID  MEALS  AVG-WAIT  MAX-WAIT\n");
    pthread_mutex_lock(&state_lock);
    for (int i = 0; i < cfg.n; i++)
        printf("  %2d  %5ld  %6.1fms  %6.1fms\n", i, meals[i],
               meals[i] ? wait_total_ns[i] / 1e6 / meals[i] : 0.0, wait_max_ns[i] / 1e6);
    pthread_mutex_unlock(&state_lock);
}

/* ------------------------------------------------------------- simulation */
static Result run_simulation(void) {
    pthread_t th[MAX_PHIL], rth;
    memset(meals, 0, sizeof meals);
    memset(wait_total_ns, 0, sizeof wait_total_ns);
    memset(wait_max_ns, 0, sizeof wait_max_ns);
    for (int i = 0; i < cfg.n; i++) {
        state[i] = mon_state[i] = THINKING;
        fork_owner[i] = -1;
        pthread_mutex_init(&forks[i], NULL);
        pthread_cond_init(&mon_cv[i], NULL);
    }
    pthread_mutex_init(&mon_lock, NULL);
    sem_init(&room, 0, cfg.n - 1);

    deadlock_flag = 0; render_stop = 0; running = 1;
    start_ns = now_ns();
    atomic_store(&last_progress, start_ns);

    for (long i = 0; i < cfg.n; i++) pthread_create(&th[i], NULL, philosopher, (void *)i);
    if (cfg.visual) pthread_create(&rth, NULL, renderer, NULL);

    /* main thread doubles as the deadlock-detecting watchdog */
    while (1) {
        sleep_ms(100);
        long long now = now_ns();
        if ((now - start_ns) / 1e9 >= cfg.duration) break;

        int hungry = 0, eating = 0;
        pthread_mutex_lock(&state_lock);
        for (int i = 0; i < cfg.n; i++) { hungry += state[i] == HUNGRY; eating += state[i] == EATING; }
        pthread_mutex_unlock(&state_lock);

        /* Deadlock = everybody is waiting, nobody is eating, and nothing has progressed for timeout_s */
        if (hungry == cfg.n && eating == 0 &&
            (now - atomic_load(&last_progress)) / 1e9 >= cfg.timeout_s) {
            deadlock_flag = 1;
            break;
        }
    }
    double elapsed = (now_ns() - start_ns) / 1e9;
    running = 0;

    if (!deadlock_flag)
        for (int i = 0; i < cfg.n; i++) pthread_join(th[i], NULL);
    /* On deadlock the threads are stuck in pthread_mutex_lock forever, so we do not join them. */

    if (cfg.visual) { render_stop = 1; pthread_join(rth, NULL); render(); }
    return compute_result(elapsed);
}

/* ------------------------------------------------------------------- main */
static void usage(const char *p) {
    printf("Usage: %s [options]\n"
           "  -n N     number of philosophers (2-%d, default 5)\n"
           "  -s NAME  strategy: naive | hierarchy | waiter | monitor | asymmetric (default hierarchy)\n"
           "  -d SEC   run duration in seconds (default 20)\n"
           "  -t MS    max thinking time in ms (default 300)\n"
           "  -e MS    max eating time in ms (default 200)\n"
           "  -w MS    naive-only delay between picking up forks (default 100)\n"
           "  -T SEC   no-progress seconds before declaring deadlock (default 3)\n"
           "  -q       quiet: no live visualization, print summary only\n"
           "  -v       force live visualization even when output is not a terminal\n"
           "  -c       compare mode: run every strategy and print a results table\n"
           "  -h       show this help\n", p, MAX_PHIL);
}

int main(int argc, char **argv) {
    cfg = (Config){ 5, HIERARCHY, 20, 300, 200, 100, 3, isatty(STDOUT_FILENO) };
    int compare = 0, opt;

    while ((opt = getopt(argc, argv, "n:s:d:t:e:w:T:qvch")) != -1) {
        switch (opt) {
        case 'n': cfg.n = atoi(optarg); break;
        case 's': {
            int ok = 0;
            for (int i = 0; i < NSTRAT; i++) if (!strcmp(optarg, strat_name[i])) { cfg.strat = i; ok = 1; }
            if (!ok) { fprintf(stderr, "Unknown strategy '%s'\n", optarg); return 1; }
            break;
        }
        case 'd': cfg.duration = atoi(optarg); break;
        case 't': cfg.think_max_ms = atoi(optarg); break;
        case 'e': cfg.eat_max_ms = atoi(optarg); break;
        case 'w': cfg.naive_delay_ms = atoi(optarg); break;
        case 'T': cfg.timeout_s = atoi(optarg); break;
        case 'q': cfg.visual = 0; break;
        case 'v': cfg.visual = 1; break;
        case 'c': compare = 1; break;
        default:  usage(argv[0]); return opt == 'h' ? 0 : 1;
        }
    }
    if (cfg.n < 2 || cfg.n > MAX_PHIL || cfg.duration < 1 ||
        cfg.think_max_ms < 1 || cfg.eat_max_ms < 1 || cfg.timeout_s < 1) {
        fprintf(stderr, "Invalid arguments (see -h)\n");
        return 1;
    }

    if (compare) {
        printf("Comparing strategies: %d philosophers, %ds each\n\n", cfg.n, cfg.duration);
        printf("%-11s %-9s %7s %9s %10s %10s %9s\n",
               "STRATEGY", "RESULT", "MEALS", "MEALS/S", "AVG-WAIT", "MAX-WAIT", "FAIRNESS");
        printf("%-11s %-9s %7s %9s %10s %10s %9s\n",
               "--------", "------", "-----", "-------", "--------", "--------", "--------");
        fflush(stdout);
        cfg.visual = 0;
        for (int s = 0; s < NSTRAT; s++) {
            pid_t pid = fork();   /* separate process per strategy: a deadlocked run can't affect the next one */
            if (pid == 0) {
                cfg.strat = s;
                Result r = run_simulation();
                printf("%-11s %-9s %7ld %9.1f %8.1fms %8.1fms %9.3f\n", strat_name[s],
                       r.deadlock ? "DEADLOCK" : "ok", r.total_meals, r.throughput,
                       r.avg_wait_ms, r.max_wait_ms, r.fairness);
                fflush(stdout);
                _exit(r.deadlock ? 2 : 0);
            }
            waitpid(pid, NULL, 0);
        }
        return 0;
    }

    Result r = run_simulation();
    print_summary(&r);
    fflush(stdout);
    if (r.deadlock) _exit(2);   /* stuck threads: terminate without joining */
    return 0;
}
