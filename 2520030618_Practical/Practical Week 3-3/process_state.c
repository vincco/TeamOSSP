#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent Process Started\n");

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed!\n");
        return 1;
    }
    else if (pid == 0)
    {
        printf("\n--- Child Process ---\n");
        printf("Child PID : %d\n", getpid());
        printf("Parent PID: %d\n", getppid());

        printf("Child is running...\n");
        sleep(5);

        printf("Child Process Finished\n");
    }
    else
    {
        printf("\n--- Parent Process ---\n");
        printf("Parent PID : %d\n", getpid());

        printf("Parent waiting for child...\n");
        wait(NULL);

        printf("Parent Process Finished\n");
    }

    return 0;
}