/*
 * main.c — Final integration
 *
 * Ties together every completed sub-module into one working
 * command-line application that behaves like a basic terminal:
 *
 *   input.c     -> read_line()       raw line capture (Session 2)
 *   history.c   -> history_add/print  command history (Session 3)
 *   tokenizer.c -> tokenize()        quoting + escaping (Sessions 4-6)
 *   builtins.c  -> is_builtin/run_builtin  cd, pwd, echo, history, help, exit
 *   executor.c  -> execute_external  fork/exec for anything on PATH
 *                  (ls, cat, grep, whoami, date, ... — covers the
 *                  "at least five commonly used commands" requirement
 *                  together with the built-ins above)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellforge.h"

static void print_prompt(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        strcpy(cwd, "?");
    }
    printf("shellforge:%s$ ", cwd);
    fflush(stdout);
}

int main(void)
{
    history_init();

    /* Non-interactive mode (input piped in / redirected from a file)
     * skips the prompt so scripted use and automated testing stay clean. */
    int interactive = isatty(STDIN_FILENO);

    while (1) {
        if (interactive) print_prompt();

        char *line = read_line();
        if (line == NULL) {
            /* EOF (Ctrl-D): exit cleanly like a real shell does */
            if (interactive) printf("\n");
            break;
        }

        history_add(line);

        char *tokens[MAX_TOKENS + 1];
        int token_count = tokenize(line, tokens);

        if (token_count > 0) {
            if (is_builtin(tokens[0])) {
                run_builtin(tokens, token_count);
            } else {
                execute_external(tokens);
            }
        } else if (token_count < 0) {
            /* tokenizer already printed a syntax error (e.g. unclosed quote) */
        }

        free_tokens(tokens, token_count > 0 ? token_count : 0);
        free(line);
    }

    history_free();
    return 0;
}
