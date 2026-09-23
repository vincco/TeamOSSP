# ShellForge

A basic Ubuntu-terminal-style shell in C, built by integrating the six
completed sub-modules (project setup, REPL loop, history, tokenizing,
quoting/escaping, and process execution) into one final application.

## Build & run

```bash
make          # compiles ./shellforge
./shellforge  # start the interactive shell
make clean    # remove build artifacts
```

Requires `gcc` and a POSIX environment (Linux/WSL/macOS). No external
dependencies.

## What it supports

**Built-in commands** (run inside the shell process, no fork):
| Command | Behavior |
|---|---|
| `cd [dir]` | change directory (defaults to `$HOME`) |
| `pwd` | print working directory |
| `echo [args...]` | print arguments |
| `history` | list previously entered commands |
| `help` | list available commands |
| `exit [code]` | quit the shell |

**External commands**: anything else is resolved against `$PATH` and run
via `fork()` + `execvp()` — e.g. `ls`, `cat`, `grep`, `whoami`, `date`,
`mkdir`, satisfying the "at least five commonly used commands" requirement
on top of the built-ins above.

**Quoting / escaping**:
- `'literal text'` — single quotes: fully literal, no escape processing inside
- `"text with spaces"` — double quotes: preserves spaces, still honors `\"`, `\\`, `\$`
- `escaped\ space` — a backslash outside quotes escapes the next character

**Error handling**: unknown commands print `command not found` instead of
crashing; unclosed quotes are reported instead of silently misparsing.

**Non-interactive mode**: if stdin isn't a terminal (e.g. `./shellforge <
script.txt`), the prompt is suppressed so it behaves well in scripts/CI.

## File layout

```
shellforge/
├── Makefile
├── README.md
├── include/
│   └── shellforge.h      shared declarations
└── src/
    ├── main.c            REPL loop — integrates every module (final deliverable)
    ├── input.c           raw line capture                (Session 2)
    ├── history.c         command history storage          (Session 3)
    ├── tokenizer.c        tokenizing, quoting, escaping    (Sessions 4-6)
    ├── builtins.c        cd / pwd / echo / history / exit  (Sessions 8-10)
    └── executor.c        fork / execvp / waitpid           (Sessions 1, 6, 7)
```

## Extending it

The module boundaries match the later sessions in the plan, so features
like pipes (`|`), redirection (`<`, `>`, `>>`), background jobs (`&`), and
signal handling (`Ctrl-C`/`Ctrl-Z`) can each be dropped into their own
`src/*.c` file and wired into `main.c` without touching the others.
