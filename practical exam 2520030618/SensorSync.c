
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t temp_pid, pressure_pid;
    int status;

    setbuf(stdout, NULL);

    printf("Gateway process started. PID: %d\n", getpid());

    temp_pid = fork();

    if (temp_pid < 0) {
        perror("Temperature fork failed");
        return 1;
    }

    if (temp_pid == 0) {
        printf("\nTemperature child started. PID: %d\n", getpid());
        printf("Temperature sensor: Reading temperature...\n");
        printf("Temperature sensor: Logging completed.\n");
        exit(0);
    }

    pressure_pid = fork();

    if (pressure_pid < 0) {
        perror("Pressure fork failed");
        waitpid(temp_pid, NULL, 0);
        return 1;
    }

    if (pressure_pid == 0) {
        printf("\nPressure child started. PID: %d\n", getpid());
        printf("Pressure sensor: Reading pressure...\n");
        printf("Pressure sensor: Logging completed.\n");
        exit(0);
    }

    printf("\nGateway waiting for both sensor processes...\n");

    if (waitpid(temp_pid, &status, 0) == -1) {
        perror("waitpid temperature");
        return 1;
    }

    if (WIFEXITED(status))
        printf("Temperature child terminated with status: %d\n",
               WEXITSTATUS(status));
    else
        printf("Temperature child did not exit normally.\n");

    if (waitpid(pressure_pid, &status, 0) == -1) {
        perror("waitpid pressure");
        return 1;
    }

    if (WIFEXITED(status))
        printf("Pressure child terminated with status: %d\n",
               WEXITSTATUS(status));
    else
        printf("Pressure child did not exit normally.\n");

    printf("\nBoth sensor readers have finished.\n");
    printf("Aggregated safety index can now be computed.\n");
    printf("Gateway process exiting. PID: %d\n", getpid());

    return 0;
}
