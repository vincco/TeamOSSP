#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void interrupt_handler(int signal) {
    printf("\nInterrupt received!\n");
}

int main() {
    signal(SIGINT, interrupt_handler);

    printf("Program is running. Press Ctrl+C to generate an interrupt.\n");

    while (1) {
        printf("Waiting...\n");
        sleep(2);
    }

    return 0;
}