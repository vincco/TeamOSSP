/*
 * input.c — Session 2 (Main Loop / Prompt / Input Capture)
 *
 * Reads one line of input from the user. getline() already gives us
 * proper backspace / cursor handling and dynamic buffer growth via
 * the terminal driver + libc, which is what sessions 2-3 (capture
 * keyboard input, handle backspace, dynamic buffers) are teaching
 * the concepts behind.
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellforge.h"

char *read_line(void)
{
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t chars_read = getline(&buffer, &bufsize, stdin);

    if (chars_read == -1) {
        /* EOF (Ctrl-D) or read error */
        free(buffer);
        return NULL;
    }

    /* strip trailing newline, if present */
    if (chars_read > 0 && buffer[chars_read - 1] == '\n') {
        buffer[chars_read - 1] = '\0';
    }

    return buffer; /* caller frees */
}
