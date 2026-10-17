
#include <stdio.h>

#define MAX 10

int n, m;
int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
int avail[MAX], seq[MAX], used[MAX];

int safeCount = 0;
int unsafeCount = 0;

/* Check whether a tenant can finish with the available resources */
int canFinish(int p, int work[]) {
    for (int j = 0; j < m; j++) {
        if (need[p][j] > work[j])
            return 0;
    }
    return 1;
}

/* Print a tenant ordering */
void printSequence(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("T%d", seq[i]);

        if (i < depth - 1)
            printf(" -> ");
    }
}

/* Check every possible ordering of tenants */
void findAllSequences(int depth, int work[]) {
    if (depth == n) {
        safeCount++;

        printf("Safe Sequence %d: ", safeCount);
        printSequence(depth);
        printf("\n");
        return;
    }

    for (int p = 0; p < n; p++) {
        if (!used[p] && canFinish(p, work)) {
            used[p] = 1;
            seq[depth] = p;

            /* Tenant finishes and releases its resources */
            for (int j = 0; j < m; j++)
                work[j] += alloc[p][j];

            findAllSequences(depth + 1, work);

            /* Backtrack */
            for (int j = 0; j < m; j++)
                work[j] -= alloc[p][j];

            used[p] = 0;
        }
    }
}

/* Enumerate all permutations and classify unsafe orderings */
void findUnsafeSequences(int depth, int work[]) {
    if (depth == n) {
        /* Replay this complete ordering from the initial state */
        int testWork[MAX];

        for (int j = 0; j < m; j++)
            testWork[j] = avail[j];

        int stuckAt = -1;

        for (int i = 0; i < n; i++) {
            int p = seq[i];

            if (!canFinish(p, testWork)) {
                stuckAt = i;
                break;
            }

            for (int j = 0; j < m; j++)
                testWork[j] += alloc[p][j];
        }

        if (stuckAt >= 0) {
            unsafeCount++;

            printf("Unsafe Sequence %d: ", unsafeCount);

            for (int i = 0; i < n; i++) {
                printf("T%d", seq[i]);

                if (i < n - 1)
                    printf(" -> ");
            }

            printf(" | Gets stuck at T%d\n", seq[stuckAt]);
        }

        return;
    }

    for (int p = 0; p < n; p++) {
        if (!used[p]) {
            used[p] = 1;
            seq[depth] = p;

            findUnsafeSequences(depth + 1, work);

            used[p] = 0;
        }
    }
}

int main(void) {
    int work[MAX];

    printf("========================================\n");
    printf("       BANKER'S ALGORITHM\n");
    printf("========================================\n");

    printf("\nEnter number of tenants and resource types: ");

    if (scanf("%d%d", &n, &m) != 2 ||
        n < 1 || n > MAX || m < 1 || m > MAX) {
        printf("Invalid input. Values must be between 1 and %d.\n", MAX);
        return 1;
    }

    printf("\nEnter Allocation Matrix (%d x %d):\n", n, m);

    for (int i = 0; i < n; i++) {
        printf("T%d: ", i);

        for (int j = 0; j < m; j++) {
            if (scanf("%d", &alloc[i][j]) != 1 ||
                alloc[i][j] < 0) {
                printf("Invalid allocation value.\n");
                return 1;
            }
        }
    }

    printf("\nEnter Maximum Claim Matrix (%d x %d):\n", n, m);

    for (int i = 0; i < n; i++) {
        printf("T%d: ", i);

        for (int j = 0; j < m; j++) {
            if (scanf("%d", &max[i][j]) != 1 ||
                max[i][j] < alloc[i][j]) {
                printf("Invalid maximum claim value.\n");
                return 1;
            }

            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("\nEnter Available Resource Vector (%d values):\n", m);

    for (int j = 0; j < m; j++) {
        if (scanf("%d", &avail[j]) != 1 || avail[j] < 0) {
            printf("Invalid available resource value.\n");
            return 1;
        }
    }

    /* Display Allocation Matrix */
    printf("\n========== ALLOCATION MATRIX ==========\n");

    for (int i = 0; i < n; i++) {
        printf("T%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);
        printf("\n");
    }

    /* Display Maximum Claim Matrix */
    printf("\n========== MAXIMUM CLAIM MATRIX ==========\n");

    for (int i = 0; i < n; i++) {
        printf("T%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }

    /* Display Need Matrix */
    printf("\n========== NEED MATRIX ==========\n");
    printf("Need = Maximum - Allocation\n");

    for (int i = 0; i < n; i++) {
        printf("T%d: ", i);
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    /* Display Available Resources */
    printf("\n========== AVAILABLE RESOURCES ==========\n");

    for (int j = 0; j < m; j++)
        printf("R%d: %d  ", j, avail[j]);

    printf("\n");

    /* Find and display all safe sequences */
    for (int i = 0; i < n; i++)
        used[i] = 0;

    for (int j = 0; j < m; j++)
        work[j] = avail[j];

    printf("\n========== ALL SAFE SEQUENCES ==========\n");
    findAllSequences(0, work);

    if (safeCount == 0)
        printf("No safe sequences exist.\n");

    /* Find and display all unsafe orderings */
    for (int i = 0; i < n; i++)
        used[i] = 0;

    printf("\n========== ALL UNSAFE SEQUENCES ==========\n");
    findUnsafeSequences(0, work);

    if (unsafeCount == 0)
        printf("No unsafe orderings exist.\n");

    /* Final summary */
    printf("\n========== FINAL RESULT ==========\n");
    printf("Total possible orderings: ");

    int total = 1;
    for (int i = 2; i <= n; i++)
        total *= i;

    printf("%d\n", total);
    printf("Total safe sequences: %d\n", safeCount);
    printf("Total unsafe sequences: %d\n", unsafeCount);

    if (safeCount > 0) {
        printf("System State: SAFE\n");
        printf("At least one complete safe sequence exists.\n");
    } else {
        printf("System State: UNSAFE\n");
        printf("No complete safe sequence exists.\n");
    }

    printf("\nNote: An unsafe ordering is one that cannot\n");
    printf("complete in that particular order. It does not\n");
    printf("necessarily mean the system is deadlocked.\n");

    return 0;
}

