#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Parent process started.\n");

    pid = fork();

    if (pid < 0)
    {
        printf("Fork failed!\n");
        exit(1);
    }

    else if (pid == 0)
    {
        // Child process
        printf("Child process started. PID = %d\n", getpid());

        printf("Child is sleeping for 3 seconds...\n");
        sleep(3);

        printf("Child process completed.\n");
        exit(0);
    }

    else
    {
        // Parent process
        printf("Parent process created child with PID = %d\n", pid);

        printf("Parent is waiting for child to finish...\n");
        wait(NULL);

        printf("Child has finished. Parent process completed.\n");
    }

    return 0;
}
