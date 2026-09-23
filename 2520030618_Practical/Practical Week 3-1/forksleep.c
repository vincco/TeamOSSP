#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;

    printf("Start of Parent\n");

    pid = fork();

    if (pid == 0)
    {
        printf("Start of Child\n");
        sleep(5);
        printf("End of Child\n");
    }
    else
    {
        sleep(10);
        printf("End of Parent\n");
    }

    return 0;
}
