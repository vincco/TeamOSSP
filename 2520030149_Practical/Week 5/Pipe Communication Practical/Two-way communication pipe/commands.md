# Commands and Concepts Used

## Two-Way Pipe Communication

This document explains the important system calls, functions, and concepts used in `twoway_pipe.c` to implement two-way communication between a parent process and a child process using unnamed pipes.

---

## 1. Header Files

### `#include <stdio.h>`

This header file provides standard input and output functions.

**Function used:**

```c
printf()
```

### Purpose

`printf()` is used to display messages and program output on the terminal.

### Example

```c
printf("I am Parent Process\n");
```

---

### `#include <unistd.h>`

This header file provides access to important UNIX system calls.

**Functions used:**

```c
pipe()
fork()
read()
write()
close()
```

These functions are used to create processes and establish communication between them.

---

### `#include <stdlib.h>`

This header file provides general utility functions.

**Function used:**

```c
exit()
```

### Purpose

`exit()` terminates the program when an error occurs.

### Example

```c
exit(1);
```

---

### `#include <string.h>`

This header file provides string handling functions.

**Function used:**

```c
strlen()
```

### Purpose

`strlen()` calculates the number of characters in a string.

### Example

```c
strlen(msg1) + 1
```

The `+1` includes the null terminating character (`'\0'`) when the message is sent through the pipe.

---

## 2. Declaring the Pipes

The program declares two pipes:

```c
int p1[2], p2[2];
```

### Purpose

Two pipes are required because a normal unnamed pipe supports communication in only one direction.

The pipes are used as follows:

```text
p1 → Parent Process to Child Process
p2 → Child Process to Parent Process
```

---

## 3. Pipe File Descriptors

Each pipe contains two file descriptors:

```text
pipe[0] → Read end
pipe[1] → Write end
```

Therefore, the two pipes in this program are used as follows:

```text
p1[0] → Read end of Pipe 1
p1[1] → Write end of Pipe 1

p2[0] → Read end of Pipe 2
p2[1] → Write end of Pipe 2
```

---

## 4. Creating the Pipes

The two pipes are created using:

```c
pipe(p1);
pipe(p2);
```

### Purpose

The `pipe()` system call creates an unnamed pipe that allows processes to exchange data.

The communication directions are:

```text
Parent Process ──── Pipe 1 ────► Child Process

Parent Process ◄─── Pipe 2 ──── Child Process
```

---

## 5. Creating the Child Process

The child process is created using:

```c
pid = fork();
```

### Purpose

The `fork()` system call creates a new process.

After `fork()` executes, the program has two processes:

```text
Original Process
       │
       ├── Parent Process
       │
       └── Child Process
```

The parent and child processes continue executing independently.

---

## 6. Checking Process Creation

The program checks whether the child process was created successfully.

```c
if (pid < 0) {
    printf("Process creation failed\n");
    exit(1);
}
```

### Explanation

If `fork()` returns a negative value, the child process could not be created.

The program then:

1. Displays an error message.
2. Terminates using `exit(1)`.

---

## 7. Identifying the Child Process

The child process is identified using:

```c
else if (pid == 0)
```

### Explanation

When `fork()` returns `0`, the currently executing process is the child process.

The program displays:

```c
printf("I am Child Process\n");
```

The child process then performs two tasks:

1. Reads the message sent by the parent.
2. Sends a response back to the parent.

---

## 8. Child Receives Message from Parent

The first pipe is used to send a message from the parent to the child.

The child closes the write end of the first pipe:

```c
close(p1[1]);
```

### Purpose

The child only needs to read from the first pipe, so the write end is not required.

The child reads the message:

```c
read(p1[0], buffer, sizeof(buffer));
```

### Explanation

```text
p1[0]          → Read end of the first pipe
buffer         → Stores the received message
sizeof(buffer) → Maximum number of bytes to read
```

The received message is displayed using:

```c
printf("Message from Parent: %s\n", buffer);
```

After reading, the child closes the read end:

```c
close(p1[0]);
```

### Communication Flow

```text
Parent
   │
   │ write()
   ▼
Pipe 1
   │
   │ read()
   ▼
Child
```

---

## 9. Child Sends Message to Parent

After receiving the parent's message, the child sends a response using the second pipe.

The child closes the unused read end:

```c
close(p2[0]);
```

The child writes the response:

```c
write(p2[1], msg2, strlen(msg2) + 1);
```

### Explanation

```text
p2[1]              → Write end of the second pipe
msg2               → Message sent by the child
strlen(msg2) + 1   → Number of bytes including '\0'
```

After writing, the child closes the write end:

```c
close(p2[1]);
```

### Communication Flow

```text
Child
   │
   │ write()
   ▼
Pipe 2
   │
   │ read()
   ▼
Parent
```

---

## 10. Identifying the Parent Process

The parent process executes the following block:

```c
else
```

The program displays:

```c
printf("I am Parent Process\n");
```

The parent process performs two tasks:

1. Sends a message to the child.
2. Reads the response sent by the child.

---

## 11. Parent Sends Message to Child

The parent uses the first pipe to send a message.

First, the parent closes the unused read end:

```c
close(p1[0]);
```

The parent writes the message:

```c
write(p1[1], msg1, strlen(msg1) + 1);
```

### Explanation

```text
p1[1]              → Write end of the first pipe
msg1               → Message sent by the parent
strlen(msg1) + 1   → Number of bytes including '\0'
```

The message sent is:

```c
char msg1[] = "Hello Child!";
```

After writing, the parent closes the write end:

```c
close(p1[1]);
```

---

## 12. Parent Receives Message from Child

The parent receives the child's response through the second pipe.

First, the parent closes the unused write end:

```c
close(p2[1]);
```

The parent reads the message:

```c
read(p2[0], buffer, sizeof(buffer));
```

The received message is displayed using:

```c
printf("Message from Child: %s\n", buffer);
```

After reading, the parent closes the read end:

```c
close(p2[0]);
```

The message received from the child is:

```c
char msg2[] = "Hello Parent!";
```

---

## 13. The `pipe()` System Call

### Syntax

```c
pipe(pipe_array);
```

### Example

```c
pipe(p1);
```

### Purpose

Creates an unnamed pipe with two file descriptors.

```text
p1[0] → Read
p1[1] → Write
```

In this program, two pipes are used to enable communication in both directions.

---

## 14. The `fork()` System Call

### Syntax

```c
pid = fork();
```

### Purpose

Creates a child process.

### Return Values

```text
pid < 0  → Process creation failed
pid == 0 → Child process
pid > 0  → Parent process
```

---

## 15. The `write()` System Call

### Syntax

```c
write(file_descriptor, data, size);
```

### Example

```c
write(p1[1], msg1, strlen(msg1) + 1);
```

### Purpose

Sends data through the write end of a pipe.

---

## 16. The `read()` System Call

### Syntax

```c
read(file_descriptor, buffer, size);
```

### Example

```c
read(p2[0], buffer, sizeof(buffer));
```

### Purpose

Reads data from the read end of a pipe and stores it in a buffer.

---

## 17. The `close()` System Call

### Syntax

```c
close(file_descriptor);
```

### Example

```c
close(p1[0]);
```

### Purpose

Closes a file descriptor that is no longer required.

Closing unused pipe ends is important because it:

- Prevents unnecessary use of system resources.
- Clearly defines which process reads and writes.
- Helps ensure proper pipe communication.

---

## 18. The `strlen()` Function

### Syntax

```c
strlen(string);
```

### Example

```c
strlen(msg1) + 1
```

### Purpose

Calculates the length of the message.

The additional `+1` ensures that the null terminating character is also transmitted:

```text
'\0'
```

This allows the received data to be correctly displayed as a C string.

---

## 19. Complete Two-Way Communication Flow

The complete communication process is:

```text
                     PIPE 1

Parent Process  ─────────────────────► Child Process
                  "Hello Child!"


                     PIPE 2

Parent Process  ◄───────────────────── Child Process
                  "Hello Parent!"
```

### Step-by-Step Flow

```text
1. Create Pipe 1.

2. Create Pipe 2.

3. Create a child process using fork().

4. The parent sends "Hello Child!" through Pipe 1.

5. The child reads the message from Pipe 1.

6. The child sends "Hello Parent!" through Pipe 2.

7. The parent reads the message from Pipe 2.

8. Both processes close the required pipe ends.

9. The program terminates.
```

---

## 20. Program Messages

The program uses two messages:

```c
char msg1[] = "Hello Child!";
char msg2[] = "Hello Parent!";
```

Their purpose is:

```text
msg1 → Sent from Parent Process to Child Process

msg2 → Sent from Child Process to Parent Process
```

The buffer used to receive messages is:

```c
char buffer[50];
```

This stores data read from the pipes.

---

## 21. Compilation Command

The program is compiled using:

```bash
clang twoway_pipe.c -o twoway_pipe
```

### Explanation

```text
clang          → C compiler

twoway_pipe.c  → Source code file

-o             → Specifies the output file name

twoway_pipe    → Name of the executable file
```

---

## 22. Execution Command

The compiled program is executed using:

```bash
./twoway_pipe
```

The `./` indicates that the executable is located in the current directory.

---

## 23. Expected Output

A typical output is:

```text
I am Parent Process
I am Child Process
Message from Parent: Hello Child!
Message from Child: Hello Parent!
```

The order of the first few lines may vary because the parent and child processes execute concurrently.

---

## 24. Difference Between One-Way and Two-Way Pipe Communication

### One-Way Pipe Communication

Data moves in only one direction:

```text
Parent ─────────────────► Child
```

Only one pipe is required.

---

### Two-Way Pipe Communication

Data moves in both directions:

```text
Parent ─────────────────► Child
Parent ◄───────────────── Child
```

Two separate pipes are required.

---

## 25. Conclusion

This program demonstrates **two-way Inter-Process Communication (IPC)** using unnamed pipes.

The parent process sends a message to the child process through the first pipe. The child receives that message and sends a response back to the parent through the second pipe.

The important concepts demonstrated in this practical are:

```text
pipe()
fork()
read()
write()
close()
strlen()
exit()
```

This practical helps in understanding how parent and child processes communicate and exchange data in UNIX-based operating systems.