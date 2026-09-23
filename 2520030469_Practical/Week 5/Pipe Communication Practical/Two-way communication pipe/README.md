# Two-Way Pipe Communication

## Objective

To implement two-way communication between a parent process and a child process using two unnamed pipes in C.

---

## Introduction

A pipe is a mechanism used for **Inter-Process Communication (IPC)** in UNIX-based operating systems.

A normal unnamed pipe allows data to flow in only one direction. Therefore, when communication is required in both directions, two separate pipes are used.

In this practical:

- The parent process sends a message to the child process through the first pipe.
- The child process sends a response back to the parent process through the second pipe.

---

## Communication Model

The communication between the parent and child processes is shown below:

```text
                     PIPE 1

Parent Process  ─────────────────────► Child Process
                  "Hello Child!"


                     PIPE 2

Parent Process  ◄───────────────────── Child Process
                  "Hello Parent!"
```

---

## Program Overview

The program performs the following operations:

1. Creates two unnamed pipes.
2. Creates a child process using `fork()`.
3. The parent process sends a message to the child using the first pipe.
4. The child process reads the message sent by the parent.
5. The child sends a response to the parent using the second pipe.
6. The parent process reads the response sent by the child.
7. Both processes close the required pipe descriptors.
8. The program terminates successfully.

---

## Program Files

The following files are included in this practical:

```text
twoway_pipe.c
README.md
commands.md
twoway_pipe
```

### File Description

| File | Description |
|---|---|
| `twoway_pipe.c` | Contains the C program implementing two-way pipe communication. |
| `README.md` | Provides an overview of the practical and program workflow. |
| `commands.md` | Explains the system calls, functions, commands, and concepts used. |
| `twoway_pipe` | Compiled executable generated from the C source file. |

---

## Source Code

The main program is contained in:

```text
twoway_pipe.c
```

The program uses two pipes:

```c
int p1[2], p2[2];
```

### Pipe Usage

```text
p1 → Parent Process to Child Process

p2 → Child Process to Parent Process
```

Each pipe contains two ends:

```text
pipe[0] → Read end

pipe[1] → Write end
```

---

## Process Creation

The program creates a child process using:

```c
pid = fork();
```

After the `fork()` system call, two processes exist:

```text
Original Program
       │
       ├── Parent Process
       │
       └── Child Process
```

Both processes execute independently.

---

## Parent-to-Child Communication

The parent sends the following message:

```text
Hello Child!
```

The message is sent through the first pipe.

### Communication Flow

```text
Parent Process
      │
      │ write()
      ▼
    Pipe 1
      │
      │ read()
      ▼
Child Process
```

The parent writes the message using:

```c
write(p1[1], msg1, strlen(msg1) + 1);
```

The child receives the message using:

```c
read(p1[0], buffer, sizeof(buffer));
```

---

## Child-to-Parent Communication

The child sends the following response:

```text
Hello Parent!
```

The response is sent through the second pipe.

### Communication Flow

```text
Child Process
      │
      │ write()
      ▼
    Pipe 2
      │
      │ read()
      ▼
Parent Process
```

The child writes the message using:

```c
write(p2[1], msg2, strlen(msg2) + 1);
```

The parent receives the message using:

```c
read(p2[0], buffer, sizeof(buffer));
```

---

## Complete Program Flow

```text
START
  │
  ▼
Create Pipe 1
  │
  ▼
Create Pipe 2
  │
  ▼
Create Child Process using fork()
  │
  ├───────────────────────────────┐
  │                               │
  ▼                               ▼
Parent Process                 Child Process
  │                               │
  │ Write "Hello Child!"           │
  │ ─────────────────────────────► │
  │          Pipe 1                │
  │                               │
  │                               │ Read Message
  │                               │
  │                               │ Write "Hello Parent!"
  │ ◄───────────────────────────── │
  │          Pipe 2                │
  │                               │
  │ Read Message                   │
  │                               │
  └───────────────┬───────────────┘
                  │
                  ▼
                 END
```

---

## Concepts Used

This practical demonstrates the following concepts:

- Inter-Process Communication (IPC)
- Parent and child processes
- Process creation using `fork()`
- Unnamed pipes
- Two-way communication
- File descriptors
- Reading data using `read()`
- Writing data using `write()`
- Closing file descriptors using `close()`
- String handling using `strlen()`
- Concurrent process execution

---

## System Calls and Functions Used

The following system calls and functions are used:

```text
pipe()
fork()
read()
write()
close()
printf()
strlen()
exit()
```

### Purpose of Each

| Function / System Call | Purpose |
|---|---|
| `pipe()` | Creates an unnamed pipe for communication between processes. |
| `fork()` | Creates a child process. |
| `read()` | Reads data from a pipe. |
| `write()` | Writes data into a pipe. |
| `close()` | Closes unused or completed pipe descriptors. |
| `printf()` | Displays output on the terminal. |
| `strlen()` | Calculates the length of a string. |
| `exit()` | Terminates the program when required. |

---

## Compilation

Compile the program using:

```bash
clang twoway_pipe.c -o twoway_pipe
```

### Command Explanation

```text
clang          → C compiler

twoway_pipe.c  → C source code file

-o             → Specifies the output file name

twoway_pipe    → Name of the executable
```

---

## Execution

Run the compiled program using:

```bash
./twoway_pipe
```

The `./` indicates that the executable is located in the current directory.

---

## Expected Output

A typical output is:

```text
I am Parent Process
I am Child Process
Message from Parent: Hello Child!
Message from Child: Hello Parent!
```

The order of the first few lines may vary because the parent and child processes execute concurrently.

---

## Difference Between One-Way and Two-Way Communication

### One-Way Pipe Communication

Data flows in only one direction:

```text
Parent Process ─────────────────► Child Process
```

Only one pipe is required.

---

### Two-Way Pipe Communication

Data flows in both directions:

```text
Parent Process ─────────────────► Child Process

Parent Process ◄───────────────── Child Process
```

Two separate pipes are required.

---

## Conclusion

This practical demonstrates **two-way Inter-Process Communication (IPC)** using two unnamed pipes.

The parent process sends a message to the child process through the first pipe. The child process receives the message and sends a response back through the second pipe.

This practical provides an understanding of how:

```text
Processes
Pipes
File Descriptors
read()
write()
fork()
```

work together to allow communication between processes in UNIX-based operating systems.