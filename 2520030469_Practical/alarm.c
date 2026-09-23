#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signal) {
    printf("\nAlarm signal received!\n");
}

int main() {
    signal(SIGALRM, alarm_handler);

    printf("Alarm set for 5 seconds...\n");

    alarm(5);

    printf("Waiting for alarm...\n");

    while (1) {
        pause();
    }

    return 0;
}