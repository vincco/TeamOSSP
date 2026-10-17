
#include <stdio.h>

#define MAX 10

int n, m;
int allocation[MAX][MAX], maximum[MAX][MAX], need[MAX][MAX];
int available[MAX], work[MAX];
int finished[MAX], sequence[MAX];
int safeCount = 0, unsafeCount = 0;

void printSequence(int seq[], int len)
{
    for (int i = 0; i < len; i++) {
        printf("T%d", seq[i] + 1);
        if (i < len - 1)
            printf(" -> ");
    }
}

int canFinish(int p)
{
    for (int j = 0; j < m; j++) {
        if (need[p][j] > work[j])
            return 0;
    }
    return 1;
}

void findSequences(int depth)
{
    if (depth == n) {
        safeCount++;
        printf("Safe sequence %d: ", safeCount);
        printSequence(sequence, n);
        printf("\n");
        return;
    }

    int found = 0;

    for (int p = 0; p < n; p++) {
        if (!finished[p] && canFinish(p)) {
            found = 1;

            for (int j = 0; j < m; j++)
                work[j] += allocation[p][j];

            finished[p] = 1;
            sequence[depth] = p;

            findSequences(depth + 1);

            finished[p] = 0;

            for (int j = 0; j < m; j++)
                work[j] -= allocation[p][j];
        }
    }

    if (!found) {
        unsafeCount++;

        printf("Unsafe/deadlocked path %d: ", unsafeCount);

        if (depth == 0) {
            printf("No tenant can execute");
        } else {
            printSequence(sequence, depth);
            printf(" -> DEADLOCK/UNSAFE");
        }

        printf("\nUnfinished tenants: ");

        for (int p = 0; p < n; p++) {
            if (!finished[p])
                printf("T%d ", p + 1);
        }

        printf("\n");
    }
}

int main(void)
{
    printf("Enter number of tenants: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    if (n < 1 || n > MAX || m < 1 || m > MAX) {
        printf("Invalid dimensions. Maximum is %d.\n", MAX);
        return 1;
    }

    printf("\nEnter Allocation matrix (%d x %d):\n", n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("\nEnter Maximum Claim matrix (%d x %d):\n", n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &maximum[i][j]);

    printf("\nEnter Available resource vector (%d values):\n", m);

    for (int j = 0; j < m; j++)
        scanf("%d", &available[j]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maximum[i][j] < allocation[i][j]) {
                printf("Invalid input: allocation exceeds maximum claim.\n");
                return 1;
            }

            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    printf("\nNeed Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    for (int j = 0; j < m; j++)
        work[j] = available[j];

    for (int i = 0; i < n; i++)
        finished[i] = 0;

    printf("\n--- All Safe Sequences ---\n");
    findSequences(0);

    printf("\n--- Summary ---\n");

    if (safeCount > 0)
        printf("System is in a SAFE state.\n");
    else
        printf("System is in an UNSAFE state.\n");

    printf("Total safe sequences: %d\n", safeCount);
    printf("Unsafe/deadlocked paths found: %d\n", unsafeCount);

    if (safeCount == 0)
        printf("No complete execution sequence exists with the given resources.\n");

    return 0;
}
