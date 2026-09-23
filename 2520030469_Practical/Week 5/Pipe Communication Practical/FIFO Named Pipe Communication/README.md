# FIFO Named Pipe Communication

## Objective

To implement communication between two separate processes using a FIFO (First In First Out), also known as a named pipe, in C.

---

## Introduction

FIFO stands for:

```text
First In First Out
```

A FIFO is also called a **named pipe** because it exists in the file system with a specific path.

Unlike an unnamed pipe created using `pipe()`, a FIFO can be used for communication between separate processes that are not necessarily related as parent and child processes.

In this practical, two separate programs are used:

- FIFO Writer
- FIFO Reader

The writer sends a message through the FIFO, and the reader receives the message.

---

## Communication Model

The communication between the writer and reader is shown below:

```text
FIFO Writer
     │
     │ write()
     ▼
/tmp/fifo_pipe
     │
     │ read()
     ▼
FIFO Reader
```

The FIFO acts as a communication channel between the two programs.

---

## Program Files

This practical contains the following files:

```text
fifo_writer.c
fifo_reader.c
README.md
commands.md
fifo_writer
fifo_reader
```

### File Description

| File | Description |
|---|---|
| `fifo_writer.c` | Contains the program that creates the FIFO and sends a message. |
| `fifo_reader.c` | Contains the program that receives and displays the message. |
| `README.md` | Provides an overview of the practical and program workflow. |
| `commands.md` | Explains the functions, system calls, and commands used. |
| `fifo_writer` | Compiled executable for the writer program. |
| `fifo_reader` | Compiled executable for the reader program. |

---

# FIFO Writer Program

## Purpose

The writer program creates the FIFO and sends a message to the reader.

The FIFO path used is:

```text
/tmp/fifo_pipe
```

The writer sends the following message:

```text
Hello receiver!
```

---

## Writer Program Flow

```text
START
  │
  ▼
Define FIFO Path
  │
  ▼
Create FIFO using mkfifo()
  │
  ▼
Wait for Reader Connection
  │
  ▼
Open FIFO in Write-Only Mode
  │
  ▼
Write Message
  │
  ▼
Display Confirmation
  │
  ▼
Close FIFO
  │
  ▼
END
```

---

# FIFO Reader Program

## Purpose

The reader program opens the same FIFO and receives the message sent by the writer.

The FIFO path used is:

```text
/tmp/fifo_pipe
```

The reader stores the received message in a character buffer and displays it on the terminal.

---

## Reader Program Flow

```text
START
  │
  ▼
Display Waiting Message
  │
  ▼
Open FIFO in Read-Only Mode
  │
  ▼
Wait for Writer
  │
  ▼
Read Message
  │
  ▼
Store Message in Buffer
  │
  ▼
Display Received Message
  │
  ▼
Close FIFO
  │
  ▼
END
```

---

# Complete Communication Flow

The complete communication process is:

```text
                    FIFO

Writer Program ───────────────► Reader Program

     │                               │
     │                               │
     ▼                               ▼

Creates FIFO                   Opens FIFO
/tmp/fifo_pipe                 /tmp/fifo_pipe

     │                               │
     │                               │
     └────── Writes Message ─────────►

             "Hello receiver!"
```

---

# Concepts Used

This practical demonstrates the following concepts:

- Inter-Process Communication (IPC)
- FIFO (First In First Out)
- Named Pipes
- Separate Processes
- File Descriptors
- FIFO Creation
- Reading Data
- Writing Data
- File Access Modes
- Process Synchronization

---

# System Calls and Functions Used

The following functions and system calls are used:

```text
mkfifo()
open()
read()
write()
close()
printf()
strlen()
```

## Purpose of Each

| Function / System Call | Purpose |
|---|---|
| `mkfifo()` | Creates a named pipe in the file system. |
| `open()` | Opens the FIFO for reading or writing. |
| `read()` | Reads data from the FIFO. |
| `write()` | Writes data into the FIFO. |
| `close()` | Closes the FIFO file descriptor. |
| `printf()` | Displays messages on the terminal. |
| `strlen()` | Calculates the length of the message. |

---

# FIFO Access Modes

The writer opens the FIFO using:

```c
O_WRONLY
```

This means:

```text
Write Only
```

The reader opens the FIFO using:

```c
O_RDONLY
```

This means:

```text
Read Only
```

The communication roles are:

```text
Writer → O_WRONLY → Sends Data

Reader → O_RDONLY → Receives Data
```

---

# Compilation

Compile the writer program using:

```bash
clang fifo_writer.c -o fifo_writer
```

Compile the reader program using:

```bash
clang fifo_reader.c -o fifo_reader
```

---

# Execution

FIFO communication requires the writer and reader to run as separate processes.

## Terminal 1 — Writer

Run:

```bash
./fifo_writer
```

The writer waits for a reader connection.

Expected message:

```text
Waiting for reader connection...
```

---

## Terminal 2 — Reader

Open another Terminal window or tab and navigate to the same directory.

Run:

```bash
./fifo_reader
```

The reader receives the message sent by the writer.

---

# Expected Output

## Writer Terminal

```text
Waiting for reader connection...
Writer sent a message.
```

## Reader Terminal

```text
Receiving message from writer...
Received message: Hello receiver!
```

---

# Important Difference: Unnamed Pipe vs FIFO

## Unnamed Pipe

Created using:

```c
pipe()
```

Usually used between related processes, such as a parent and child process.

Example:

```text
Parent Process ─────► Child Process
```

---

## FIFO Named Pipe

Created using:

```c
mkfifo()
```

Uses a named path in the file system.

Example:

```text
Writer ─────► /tmp/fifo_pipe ─────► Reader
```

Separate programs can communicate through the same FIFO.

---

# Conclusion

This practical demonstrates Inter-Process Communication using a FIFO, also known as a named pipe.

The writer program creates and opens the FIFO, then sends a message. The reader program opens the same FIFO, receives the message, and displays it.

The practical demonstrates how separate processes can communicate using:

```text
mkfifo()
open()
read()
write()
close()
```

FIFO communication is an important UNIX and Linux mechanism for exchanging data between independent processes.