/*
 * builtins.c — Sessions 8, 9, 10 (Built-in Dispatch Table)
 *
 * Built-ins run IN the shell process (no fork), because things like
 * `cd` and `exit` only make sense if they mutate the shell's own state.
 * This gives us 5 always-available commands even with an empty PATH:
 *   cd, pwd, exit, echo, history
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "shellforge.h"

static const char *BUILTIN_NAMES[] = {
    "cd", "pwd", "exit", "echo", "history", "help", NULL
};

int is_builtin(const char *cmd)
{
    for (int i = 0; BUILTIN_NAMES[i] != NULL; i++) {
        if (strcmp(cmd, BUILTIN_NAMES[i]) == 0) return 1;
    }
    return 0;
}

static void builtin_cd(char **argv, int argc)
{
    const char *target;

    if (argc < 2) {
        target = getenv("HOME");
        if (!target) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
    } else {
        target = argv[1];
    }

    if (chdir(target) != 0) {
        fprintf(stderr, "cd: %s: %s\n", target, strerror(errno));
    }
}

static void builtin_pwd(void)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

static void builtin_echo(char **argv, int argc)
{
    for (int i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i < argc - 1) printf(" ");
    }
    printf("\n");
}

static void builtin_help(void)
{
    printf("ShellForge — basic Ubuntu-style terminal\n");
    printf("Built-in commands:\n");
    printf("  cd [dir]     change working directory (default: $HOME)\n");
    printf("  pwd          print working directory\n");
    printf("  echo [args]  print arguments\n");
    printf("  history      show command history\n");
    printf("  help         show this message\n");
    printf("  exit [code]  exit the shell\n");
    printf("Any other command is looked up on PATH and executed (ls, cat, grep, ...).\n");
}

int run_builtin(char **argv, int argc)
{
    const char *cmd = argv[0];

    if (strcmp(cmd, "cd") == 0) {
        builtin_cd(argv, argc);
    } else if (strcmp(cmd, "pwd") == 0) {
        builtin_pwd();
    } else if (strcmp(cmd, "echo") == 0) {
        builtin_echo(argv, argc);
    } else if (strcmp(cmd, "history") == 0) {
        history_print();
    } else if (strcmp(cmd, "help") == 0) {
        builtin_help();
    } else if (strcmp(cmd, "exit") == 0) {
        int code = 0;
        if (argc >= 2) code = atoi(argv[1]);
        history_free();
        exit(code);
    }

    return 0;
}
