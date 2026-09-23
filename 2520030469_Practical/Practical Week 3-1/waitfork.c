#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid;

    printf("Start of Parent\n");

    pid = fork();      // Create child process

    if (pid == 0)      // Body of child process
    {
        printf("Start of Child\n");
        sleep(15);     // Child process sleeps for 15 sec
        exit(0);       // Force termination of child process
        printf("End of Child\n");
    }
    else               // Body of parent process
    {
        sleep(10);     // Parent process sleeps for 10 sec
        wait(NULL);    // Parent waits for child process to complete
        printf("End of Parent\n");
    }

    return 0;
}
