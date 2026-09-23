/*
 * executor.c — Sessions 1, 6, 7 (Process Creation, execve family, PATH
 * resolution, waitpid synchronization)
 *
 * execvp() does the PATH search + exec for us (that's what makes it
 * the "p" variant), so this module focuses on the fork/exec/wait
 * lifecycle and turning failures into the same kind of message a
 * real shell prints ("command not found").
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "shellforge.h"

void execute_external(char **argv)
{
    pid_t pid = fork();

    if (pid < 0) {
        perror("shellforge: fork failed");
        return;
    }

    if (pid == 0) {
        /* child: replace this process image with the requested program */
        execvp(argv[0], argv);

        /* execvp only returns on failure */
        if (errno == ENOENT) {
            fprintf(stderr, "shellforge: %s: command not found\n", argv[0]);
        } else {
            fprintf(stderr, "shellforge: %s: %s\n", argv[0], strerror(errno));
        }
        _exit(127); /* standard "command not found" exit status */
    }

    /* parent: wait for the child (Session 7 — waitpid synchronization) */
    int status;
    waitpid(pid, &status, 0);
    /* status is available here for a future exit-code / job-control feature */
}
