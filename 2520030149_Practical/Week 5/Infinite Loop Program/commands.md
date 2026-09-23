# Commands and Concepts Used – Infinite Loop Program

This document explains the important C statements, functions, commands, and concepts used in the `infiniteloop.c` program.

---

# 1. Header File

## `#include <stdio.h>`

This header file provides standard input and output functions.

The program uses:

```c
printf()
```

### Purpose

`printf()` is used to display output on the terminal.

Example:

```c
printf("SHS\n");
```

This displays:

```text
SHS
```

The `\n` moves the cursor to the next line.

---

# 2. The `main()` Function

The program execution begins from:

```c
int main()
```

The complete structure is:

```c
int main() {

    // Program statements

    return 0;
}
```

The `main()` function is the starting point of a C program.

---

# 3. The `while` Loop

The program uses:

```c
while (1)
```

A `while` loop repeatedly executes a block of code as long as its condition is true.

## General Syntax

```c
while (condition) {
    // Statements to repeat
}
```

Example:

```c
while (1) {
    printf("SHS\n");
}
```

---

# 4. Why `while(1)` Creates an Infinite Loop

In C programming:

```text
0 → False

Non-zero value → True
```

Since:

```c
1
```

is always a non-zero value, it always evaluates to:

```text
TRUE
```

Therefore:

```c
while (1)
```

means:

```text
Repeat forever
```

The condition never becomes false.

---

# 5. Infinite Loop

An infinite loop is a loop that continues executing indefinitely.

The flow is:

```text
while(1)
   │
   ▼
Condition = TRUE
   │
   ▼
Execute printf()
   │
   ▼
Check condition again
   │
   ▼
Condition = TRUE
   │
   └───────────────↺
```

Because the condition always remains true, the loop continues forever.

---

# 6. `printf()` Function

The program uses:

```c
printf("SHS\n");
```

## Purpose

`printf()` displays output on the terminal.

The statement:

```c
printf("SHS\n");
```

does two things:

```text
1. Prints SHS
2. Moves to the next line
```

The `\n` represents a newline character.

---

# 7. Loop Body

The statements inside the braces are called the loop body.

Example:

```c
while (1) {
    printf("SHS\n");
}
```

The loop body is:

```c
{
    printf("SHS\n");
}
```

Every time the loop repeats, this statement executes again.

---

# 8. Program Execution Flow

The complete program flow is:

```text
START
  │
  ▼
Enter main()
  │
  ▼
while(1)
  │
  ▼
Condition is TRUE
  │
  ▼
Execute printf()
  │
  ▼
Print SHS
  │
  ▼
Return to while(1)
  │
  └────────────────↺
```

This continues until the program is manually interrupted.

---

# 9. Compiling the Program

The program is compiled using:

```bash
clang infiniteloop.c -o infiniteloop
```

## Command Breakdown

```text
clang
│
└── C compiler


infiniteloop.c
│
└── C source code file


-o
│
└── Specifies the output file name


infiniteloop
│
└── Name of the generated executable
```

After successful compilation:

```text
infiniteloop.c
        │
        ▼
      clang
        │
        ▼
  infiniteloop
```

---

# 10. Running the Program

The compiled program is executed using:

```bash
./infiniteloop
```

## Meaning of `./`

```text
.
│
└── Current directory


/
│
└── Path separator


infiniteloop
│
└── Executable program
```

The command tells the system:

```text
Run the executable named infiniteloop
from the current directory.
```

---

# 11. Expected Output

The program continuously prints:

```text
SHS
SHS
SHS
SHS
SHS
SHS
...
```

The output continues because the loop condition never becomes false.

---

# 12. Stopping the Infinite Loop

Since the program does not stop automatically, it must be manually interrupted.

Press:

```text
Control + C
```

This sends an interrupt signal to the running program.

The flow is:

```text
Program Running
      │
      ▼
while(1)
      │
      ▼
Continuous Execution
      │
      ▼
Control + C
      │
      ▼
Program Stops
      │
      ▼
Terminal Prompt Returns
```

---

# 13. `return 0`

The program contains:

```c
return 0;
```

This normally indicates successful completion of the `main()` function.

However, in this program:

```c
while (1)
```

runs indefinitely.

Therefore, the program normally does not reach:

```c
return 0;
```

unless the infinite loop is changed or removed.

---

# 14. Complete Source Program

```c
#include <stdio.h>

int main() {

    while (1) {
        printf("SHS\n");
    }

    return 0;
}
```

---

# 15. Important Concepts Learned

This program demonstrates:

```text
C Program Structure
        ↓
Header Files
        ↓
main() Function
        ↓
while Loop
        ↓
Boolean Evaluation
        ↓
Infinite Loop
        ↓
Repeated Execution
        ↓
Manual Program Termination
```

---

# Conclusion

This program demonstrates the working of an infinite loop using:

```c
while (1)
```

Since `1` always evaluates to true, the loop continues repeatedly and executes:

```c
printf("SHS\n");
```

The program must be manually stopped using:

```text
Control + C
```

This practical helps demonstrate how loop conditions control program execution and how an always-true condition creates an infinite loop.