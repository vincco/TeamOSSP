/*
 * tokenizer.c — Sessions 4, 5, 6
 *   Session 4: split input into tokens, delimiters, whitespace handling
 *   Session 5: single-quote (literal) and double-quote (preserve spaces) handling
 *   Session 6: backslash escape sequences
 *
 * Rules implemented:
 *   'text'   -> literal, no escapes processed inside
 *   "text"   -> spaces preserved, backslash still escapes " and \ and space
 *   \x       -> outside quotes, the next char is taken literally (lets you
 *               escape spaces, quotes, or backslashes themselves)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shellforge.h"

int tokenize(const char *line, char **tokens)
{
    int token_count = 0;
    size_t i = 0;
    size_t len = strlen(line);

    while (i < len && token_count < MAX_TOKENS) {
        /* skip leading whitespace (delimiters) */
        while (i < len && isspace((unsigned char)line[i])) {
            i++;
        }
        if (i >= len) break;

        char *current = malloc(MAX_TOKEN_LEN);
        if (!current) {
            fprintf(stderr, "shellforge: allocation failure\n");
            free_tokens(tokens, token_count);
            return -1;
        }
        size_t pos = 0;

        /* consume one token: keeps going through quoted/escaped
         * spans even if they contain whitespace */
        while (i < len && !isspace((unsigned char)line[i])) {
            char c = line[i];

            if (c == '\'') {
                /* single-quoted: fully literal until closing quote */
                i++;
                while (i < len && line[i] != '\'') {
                    if (pos < MAX_TOKEN_LEN - 1) current[pos++] = line[i];
                    i++;
                }
                if (i >= len) {
                    fprintf(stderr, "shellforge: unclosed single quote\n");
                    free(current);
                    free_tokens(tokens, token_count);
                    return -1;
                }
                i++; /* skip closing quote */
            } else if (c == '"') {
                /* double-quoted: spaces preserved, backslash still works
                 * for \" \\ and \$ (variable-expansion placeholder) */
                i++;
                while (i < len && line[i] != '"') {
                    if (line[i] == '\\' && i + 1 < len &&
                        (line[i + 1] == '"' || line[i + 1] == '\\' || line[i + 1] == '$')) {
                        i++;
                        if (pos < MAX_TOKEN_LEN - 1) current[pos++] = line[i];
                        i++;
                    } else {
                        if (pos < MAX_TOKEN_LEN - 1) current[pos++] = line[i];
                        i++;
                    }
                }
                if (i >= len) {
                    fprintf(stderr, "shellforge: unclosed double quote\n");
                    free(current);
                    free_tokens(tokens, token_count);
                    return -1;
                }
                i++; /* skip closing quote */
            } else if (c == '\\') {
                /* bare escape outside quotes: next char taken literally,
                 * including a space, so "foo\ bar" is ONE token */
                i++;
                if (i < len) {
                    if (pos < MAX_TOKEN_LEN - 1) current[pos++] = line[i];
                    i++;
                }
            } else {
                if (pos < MAX_TOKEN_LEN - 1) current[pos++] = line[i];
                i++;
            }
        }

        current[pos] = '\0';
        tokens[token_count++] = current;
    }

    tokens[token_count] = NULL; /* NULL-terminate, execvp-style */
    return token_count;
}

void free_tokens(char **tokens, int count)
{
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
        tokens[i] = NULL;
    }
}
