#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    char bfr[100];

    printf("Receiving message from writer...\n");

    int fd = open("/tmp/fifo_pipe", O_RDONLY);

    read(fd, bfr, sizeof(bfr));

    printf("Received message: %s", bfr);

    close(fd);

    return 0;
}