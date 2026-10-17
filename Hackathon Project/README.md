# Dining Philosophers Deadlock Prevention System

A C / POSIX-threads simulator that **demonstrates deadlock** in the classic Dining
Philosophers problem and compares **four prevention strategies**, with a live
terminal visualization, a watchdog deadlock detector, and starvation/fairness metrics.

## Requirements
- Linux (or WSL on Windows), `gcc`, `make`, POSIX threads and semaphores
- macOS note: unnamed POSIX semaphores (`sem_init`) are unsupported; use Linux/WSL

## Build
```bash
make          # produces ./dining
make clean
```

## Run
```bash
./dining -s naive -n 5            # watch it deadlock
./dining -s hierarchy -n 5        # resource ordering
./dining -s waiter -n 5           # semaphore (max N-1 at the table)
./dining -s monitor -n 5          # monitor + condition variables
./dining -s asymmetric -n 5       # even/odd pick opposite fork first
./dining -c -d 10                 # compare all strategies (results table)
make test                         # automated validation
```

| Option | Meaning | Default |
|---|---|---|
| `-n N` | philosophers (2-64) | 5 |
| `-s NAME` | strategy | hierarchy |
| `-d SEC` | run duration | 20 |
| `-t MS` / `-e MS` | max think / eat time | 300 / 200 |
| `-w MS` | naive-only delay between forks | 100 |
| `-T SEC` | no-progress time before deadlock is declared | 3 |
| `-q` / `-v` | no visualization / force visualization | auto |
| `-c` | compare mode | off |

## Strategies and the Coffman condition each one breaks
| Strategy | Mechanism | Breaks |
|---|---|---|
| naive | left fork, then right fork | nothing, so it deadlocks |
| hierarchy | always lock the lower-numbered fork first | circular wait |
| waiter | `sem_t` allows at most N-1 philosophers to compete | circular wait (one always can finish) |
| monitor | `pthread_mutex_t` + `pthread_cond_t`, take both forks atomically | hold and wait |
| asymmetric | even ids go left-first, odd ids right-first | symmetry, hence circular wait |

## How it works
- Each philosopher is a `pthread`; each fork is a `pthread_mutex_t`.
- All philosophers start hungry at t=0 (worst case) so the naive deadlock is reproducible.
- **Deadlock detector:** the main thread watches progress. If every philosopher is HUNGRY,
  nobody is EATING and no meal has started for `-T` seconds, a deadlock is reported.
- **Metrics:** meals per philosopher, throughput, average/max wait (starvation indicator),
  and Jain's fairness index (1.0 = perfectly fair).
- Compare mode runs each strategy in a separate `fork()`ed process so a deadlocked run
  cannot affect the next one.
- The simulation only uses its own threads and mutexes and does not touch other processes.

## Testing
`make test` checks that naive deadlocks, and that each other strategy runs without deadlock
with 2, 5 and 20 philosophers.

## Project layout
```
dining.c            simulator source
Makefile
tests/run_tests.sh  automated tests
README.md
```
