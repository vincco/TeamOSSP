#ifndef SHELLFORGE_H
#define SHELLFORGE_H

#define MAX_TOKENS      64
#define MAX_TOKEN_LEN   1024
#define MAX_HISTORY     200

/* ---- input.c ---- */
char *read_line(void);

/* ---- tokenizer.c ----
 * Splits a raw input line into an argv-style array of tokens,
 * honoring single quotes, double quotes and backslash escapes.
 * Returns the number of tokens found (0 for an empty/blank line).
 * Caller does NOT need to free individual tokens; tokenizer owns
 * a static-lifetime pool that is reused / freed via free_tokens().
 */
int tokenize(const char *line, char **tokens);
void free_tokens(char **tokens, int count);

/* ---- history.c ---- */
void history_init(void);
void history_add(const char *line);
void history_print(void);
void history_free(void);

/* ---- builtins.c ---- */
int is_builtin(const char *cmd);
/* returns 1 if the shell should exit after this call */
int run_builtin(char **argv, int argc);

/* ---- executor.c ---- */
void execute_external(char **argv);

#endif
