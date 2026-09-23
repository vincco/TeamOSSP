#include <stdio.h>
#include <signal.h>

void handler(int signal) {
    printf("Signal received: %d\n", signal);
}

int main() {
    signal(SIGFPE, handler);

    printf("Raising SIGFPE...\n");

    raise(SIGFPE);

    printf("Program continues after handling the signal.\n");

    return 0;
}