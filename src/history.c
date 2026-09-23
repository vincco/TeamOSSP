/*
 * history.c — Session 3 (Store Command History / Navigate / Buffers)
 *
 * Simple ring-capacity dynamic array. Full arrow-key recall would need
 * raw terminal mode (termios) to trap escape sequences; here we expose
 * the storage + a `history` builtin to display it, which covers the
 * "store, retrieve, display, validate consistency" learning goals
 * without hijacking the terminal's own line editing.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellforge.h"

static char *entries[MAX_HISTORY];
static int count = 0;

void history_init(void)
{
    count = 0;
    memset(entries, 0, sizeof(entries));
}

void history_add(const char *line)
{
    if (line == NULL || line[0] == '\0') return; /* skip blank commands */

    if (count == MAX_HISTORY) {
        /* capacity limit reached: drop oldest, shift left */
        free(entries[0]);
        memmove(&entries[0], &entries[1], sizeof(char *) * (MAX_HISTORY - 1));
        count--;
    }

    entries[count++] = strdup(line);
}

void history_print(void)
{
    for (int i = 0; i < count; i++) {
        printf("%5d  %s\n", i + 1, entries[i]);
    }
}

void history_free(void)
{
    for (int i = 0; i < count; i++) {
        free(entries[i]);
        entries[i] = NULL;
    }
    count = 0;
}
