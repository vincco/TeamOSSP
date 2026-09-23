# Commands and Concepts Used – One-Way Pipe Communication

This document explains the important **C functions, system calls, variables, file descriptors, and IPC concepts** used in the `one_way_pipe.c` program.

---

# 1. Header Files

## 1.1 Standard Input and Output

```c
#include <stdio.h>
```

This header provides standard input and output functions.

### Functions Used

```c
printf()
perror()
```

### `printf()`

Used to display messages on the terminal.

Example:

```c
printf("I am in Parent Process\n");
```

Another example:

```c
printf("I am in Child Process\n");
```

---

### `perror()`

Used to display an error message when a system call fails.

Example:

```c
perror("Failed to create pipe");
```

---

## 1.2 POSIX System Calls

```c
#include <unistd.h>
```

This header provides access to important POSIX system calls.

### Functions Used

```c
pipe()
fork()
read()
write()
close()
```

These functions are responsible for:

- Creating processes
- Creating pipes
- Reading data
- Writing data
- Closing file descriptors

---

## 1.3 Standard Utility Functions

```c
#include <stdlib.h>
```

This header provides general utility functions.

### Function Used

```c
exit()
```

### `exit()`

Terminates the program.

Example:

```c
exit(1);
```

A non-zero value usually indicates that the program ended because of an error.

---

## 1.4 String Handling Functions

```c
#include <string.h>
```

This header provides functions used for string operations.

### Function Used

```c
strlen()
```

### `strlen()`

Returns the number of characters in a string.

Example:

```c
strlen(msg)
```

The returned value is used to determine how many characters should be written into the pipe.

---

# 2. Process ID Variable

```c
int pid;
```

This variable stores the value returned by:

```c
fork()
```

The value of `pid` helps identify whether the current process is the parent or the child.

```text
pid < 0   → Process creation failed
pid == 0  → Child Process
pid > 0   → Parent Process
```

---

# 3. Pipe File Descriptors

```c
int fd[2];
```

A pipe uses two file descriptors.

```text
fd[0] → Read end of the pipe
fd[1] → Write end of the pipe
```

The communication structure is:

```text
Parent Process
      │
      │ write(fd[1])
      ▼
    PIPE
      │
      │ read(fd[0])
      ▼
Child Process
```

---

# 4. Creating the Pipe

```c
pipe(fd)
```

The `pipe()` system call creates a pipe for communication between processes.

The two ends of the pipe are stored in the `fd` array:

```text
fd[0] → Read end
fd[1] → Write end
```

The program checks whether the pipe was created successfully:

```c
if (pipe(fd) == -1)
{
    perror("Failed to create pipe");
    exit(1);
}
```

If `pipe()` fails:

1. An error message is displayed.
2. The program terminates.

---

# 5. Creating a Child Process

```c
pid = fork();
```

The `fork()` system call creates a new child process.

After `fork()` executes:

```text
Original Process
       │
       │ fork()
       ▼
 ┌─────────────┐
 │             │
Parent       Child
```

Both processes continue execution from the point after the `fork()` call.

---

# 6. Checking for Process Creation Failure

```c
if (pid < 0)
{
    printf("Failure in process creation\n");
    exit(1);
}
```

If the `fork()` system call fails:

- `pid` becomes negative.
- An error message is displayed.
- The program terminates.

---

# 7. Child Process

```c
else if (pid == 0)
```

This block is executed by the child process.

The child process is responsible for:

1. Closing the unused write end of the pipe.
2. Reading the message from the pipe.
3. Displaying the received message.
4. Closing the read end.

---

# 8. Closing the Write End in the Child

```c
close(fd[1]);
```

The child only needs to read data.

Therefore, the child closes:

```text
fd[1] → Write end
```

The child continues using:

```text
fd[0] → Read end
```

---

# 9. Reading Data from the Pipe

```c
int bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
```

The `read()` system call reads data from the pipe.

### Parameters

```text
fd[0]              → Read end of the pipe
buffer             → Stores the received message
sizeof(buffer) - 1 → Maximum number of characters to read
```

The number of bytes successfully read is stored in:

```c
bytesRead
```

---

# 10. Checking the Read Operation

```c
if (bytesRead > 0)
```

This checks whether data was successfully read from the pipe.

If one or more bytes are received, the program continues to process the message.

---

# 11. Adding the Null Character

```c
buffer[bytesRead] = '\0';
```

The `read()` system call returns raw bytes.

To safely print the received data as a C string, the null character is added at the end:

```text
'\0'
```

This marks the end of the string.

Example:

```text
Before termination:
hello child!

After termination:
hello child!\0
```

---

# 12. Displaying the Received Message

```c
printf("Message from parent: %s\n", buffer);
```

The `%s` format specifier displays the string stored in `buffer`.

Example output:

```text
Message from parent: hello child!
```

---

# 13. Closing the Read End in the Child

```c
close(fd[0]);
```

After reading the message, the child closes the read end of the pipe.

This releases the file descriptor.

---

# 14. Parent Process

```c
else
```

This block is executed by the parent process.

The parent process is responsible for:

1. Closing the unused read end.
2. Writing a message into the pipe.
3. Closing the write end.

---

# 15. Closing the Read End in the Parent

```c
close(fd[0]);
```

The parent does not need to read data from the pipe.

Therefore, it closes:

```text
fd[0] → Read end
```

The parent continues using:

```text
fd[1] → Write end
```

---

# 16. Writing Data into the Pipe

```c
write(fd[1], msg, strlen(msg));
```

The `write()` system call sends data into the pipe.

### Parameters

```text
fd[1]       → Write end of the pipe
msg         → Message to send
strlen(msg) → Number of characters to send
```

The message:

```text
hello child!
```

is sent by the parent process through the pipe.

---

# 17. Closing the Write End in the Parent

```c
close(fd[1]);
```

After sending the message, the parent closes the write end.

This indicates that the parent has finished writing to the pipe.

---

# 18. One-Way Communication

This program uses a single pipe.

Communication happens in only one direction:

```text
Parent Process
      │
      │ write()
      ▼
    PIPE
      │
      │ read()
      ▼
Child Process
```

The child does not send any message back to the parent.

Therefore, this is called:

```text
One-Way Communication
```

It is also called:

```text
Unidirectional Pipe Communication
```

---

# 19. Complete Program Flow

```text
Start Program
      │
      ▼
Create Pipe using pipe()
      │
      ▼
Was the pipe created successfully?
      │
      ├── No → Display Error → End Program
      │
      └── Yes
            │
            ▼
      Create Child using fork()
            │
            ▼
      Did fork() succeed?
            │
            ├── No → Display Error → End Program
            │
            └── Yes
                  │
                  ▼
        ┌─────────────────┐
        │                 │
      Parent            Child
        │                 │
   Close fd[0]      Close fd[1]
        │                 │
   Write message      Read message
        │                 │
   Close fd[1]       Add '\0'
                          │
                    Display message
                          │
                     Close fd[0]
```

---

# 20. Compilation Command

Compile the program using:

```bash
clang one_way_pipe.c -o one_way_pipe
```

### Command Breakdown

```text
clang           → C compiler
one_way_pipe.c  → Source code file
-o              → Specifies the output file name
one_way_pipe    → Name of the compiled executable
```

---

# 21. Execution Command

Run the compiled program using:

```bash
./one_way_pipe
```

### Command Breakdown

```text
./              → Current directory
one_way_pipe    → Executable program
```

---

# 22. Important File Descriptor Concept

After creating the pipe:

```text
fd[0] → Used for reading
fd[1] → Used for writing
```

The processes close the pipe ends they do not use.

### Parent Process

```text
Closes → fd[0]
Uses   → fd[1]
```

### Child Process

```text
Closes → fd[1]
Uses   → fd[0]
```

This creates the following one-way communication path:

```text
Parent
   │
   │ write(fd[1])
   ▼
┌──────────┐
│   PIPE   │
└──────────┘
   │
   │ read(fd[0])
   ▼
Child
```

---

# Summary

This program demonstrates **one-way Inter-Process Communication using a pipe**.

The main system calls used are:

```c
pipe()
fork()
read()
write()
close()
```

The complete communication flow is:

```text
Parent Process
      │
      │ Sends Message
      ▼
     PIPE
      │
      │ Transfers Message
      ▼
Child Process
      │
      ▼
Displays Message
```

The parent sends the message, and the child receives and displays it. Since communication occurs only from the parent to the child, this program demonstrates **unidirectional pipe communication**.