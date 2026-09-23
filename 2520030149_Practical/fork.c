#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Before fork()\n");
    printf("Current Process ID (PID): %d\n", getpid());
    printf("Parent Process ID (PPID): %d\n\n", getppid());

    pid = fork();

    if (pid < 0)
    {
        // Fork failed
        printf("Fork failed!\n");
        return 1;
    }

    else if (pid == 0)
    {
        // Child process
        printf("----- CHILD PROCESS -----\n");
        printf("Child PID  : %d\n", getpid());
        printf("Child PPID : %d\n", getppid());
        printf("fork() returned: %d\n", pid);
    }

    else
    {
        // Parent process
        printf("----- PARENT PROCESS -----\n");
        printf("Parent PID : %d\n", getpid());
        printf("Parent PPID: %d\n", getppid());
        printf("Child PID  : %d\n", pid);

        wait(NULL);

        printf("Child process has finished.\n");
    }

    return 0;
}
