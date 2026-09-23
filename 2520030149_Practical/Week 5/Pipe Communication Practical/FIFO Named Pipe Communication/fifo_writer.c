#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main() {
    char *path = "/tmp/fifo_pipe";

    mkfifo(path, 0666);

    printf("Waiting for reader connection...\n");

    char msg[] = "Hello receiver!\n";

    int fd = open(path, O_WRONLY);

    write(fd, msg, strlen(msg));

    printf("Writer sent a message.\n");

    close(fd);

    return 0;
}