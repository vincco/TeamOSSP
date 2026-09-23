#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void interrupt_handler(int signal) {
    printf("\nInterrupt received!\n");
}

void segmentation_handler(int signal) {
    printf("\nSegmentation fault signal received!\n");
    printf("Program terminating...\n");
    _exit(1);
}

int main() {
    signal(SIGINT, interrupt_handler);
    signal(SIGSEGV, segmentation_handler);

    printf("Program started.\n");
    printf("Press Ctrl+C for interrupt.\n");

    sleep(3);

    printf("Generating segmentation fault...\n");

    int *ptr = NULL;
    *ptr = 10;

    return 0;
}