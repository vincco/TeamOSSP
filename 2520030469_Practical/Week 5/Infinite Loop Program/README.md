# Infinite Loop Program

## Objective

To demonstrate the working of an infinite loop in C using the `while(1)` statement.

---

## Introduction

A loop is used in programming to repeatedly execute a block of code.

An infinite loop is a loop whose condition always remains true, causing the program to continue executing indefinitely unless it is manually terminated.

In this program:

```c
while (1)
```

The value `1` represents true in C, so the loop condition never becomes false.

---

## Program Description

The program repeatedly prints:

```text
SHS
```

because the `printf()` statement is placed inside an infinite `while` loop.

The program continues executing until it is manually stopped.

---

## Source Code

The program is stored in:

```text
infiniteloop.c
```

The main loop used in the program is:

```c
while (1) {
    printf("SHS\n");
}
```

---

## Program Flow

```text
START
  │
  ▼
Enter main()
  │
  ▼
Check while(1)
  │
  ▼
Condition is TRUE
  │
  ▼
Print "SHS"
  │
  ▼
Return to while(1)
  │
  └───────────────↺
```

Since the condition is always true, the program continues indefinitely.

---

## Concepts Used

This program demonstrates:

- Looping in C
- `while` loop
- Infinite loop
- Boolean evaluation of `1`
- Repeated execution
- Program termination using keyboard interrupt

---

## Header File Used

```c
#include <stdio.h>
```

This header file provides standard input and output functions.

It is required for:

```c
printf()
```

---

## Compilation

Compile the program using:

```bash
clang infiniteloop.c -o infiniteloop
```

### Command Explanation

```text
clang
│
└── C compiler

infiniteloop.c
│
└── Source code file

-o
│
└── Specifies the output file name

infiniteloop
│
└── Generated executable
```

---

## Execution

Run the program using:

```bash
./infiniteloop
```

The program will continuously display:

```text
SHS
SHS
SHS
SHS
SHS
...
```

---

## Stopping the Program

Since this is an infinite loop, the program does not terminate automatically.

To stop the program, press:

```text
Control + C
```

This sends an interrupt signal to the running program and returns control to the Terminal.

---

## Important Concept

The condition:

```c
while (1)
```

means:

```text
1 → TRUE
```

Therefore:

```text
Condition is TRUE
       │
       ▼
Execute loop body
       │
       ▼
Check condition again
       │
       ▼
Still TRUE
       │
       └──────────────↺
```

The loop continues until the program is externally interrupted.

---

## Expected Output

A typical output is:

```text
SHS
SHS
SHS
SHS
SHS
SHS
...
```

The number of lines printed depends on how long the program is allowed to run before it is manually stopped.

---

## Program Files

```text
infiniteloop.c
README.md
commands.md
infiniteloop
```

| File | Description |
|---|---|
| `infiniteloop.c` | Contains the C program demonstrating an infinite loop. |
| `README.md` | Provides an overview of the program and its working. |
| `commands.md` | Explains the functions, statements, and concepts used. |
| `infiniteloop` | Compiled executable generated from the source code. |

---

## Conclusion

This program demonstrates how an infinite loop works in C using:

```c
while (1)
```

Because the condition always evaluates to true, the `printf()` statement continues executing repeatedly until the program is manually terminated using:

```text
Control + C
```