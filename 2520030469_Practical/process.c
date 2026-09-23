#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    printf("----- PROCESS INFORMATION -----\n");

    printf("Process ID (PID)  : %d\n", getpid());
    printf("Parent PID (PPID) : %d\n", getppid());

    printf("\nThis is a single process.\n");
    printf("No child process is created.\n");

    return 0;
}
