#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pid;
    int fd[2];

    char msg[] = "hello child!";
    char buffer[20];

    // Create a pipe
    if (pipe(fd) == -1)
    {
        perror("Failed to create pipe");
        exit(1);
    }

    // Create child process
    pid = fork();

    if (pid < 0)
    {
        printf("Failure in process creation\n");
        exit(1);
    }

    // Child Process
    else if (pid == 0)
    {
        printf("I am in Child Process\n");

        // Child does not write to the pipe
        close(fd[1]);

        // Read message from parent
        int bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);

        if (bytesRead > 0)
        {
            buffer[bytesRead] = '\0';

            printf("Message from parent: %s\n", buffer);
        }

        close(fd[0]);
    }

    // Parent Process
    else
    {
        printf("I am in Parent Process\n");

        // Parent does not read from the pipe
        close(fd[0]);

        // Send message to child
        write(fd[1], msg, strlen(msg));

        close(fd[1]);
    }

    return 0;
}