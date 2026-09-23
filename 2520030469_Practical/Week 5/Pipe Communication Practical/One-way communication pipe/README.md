# One-Way Pipe Communication

## Objective

To understand **Inter-Process Communication (IPC)** using a pipe and demonstrate **one-way communication** between a parent process and a child process.

---

# Program Description

This program demonstrates communication between two processes created using the `fork()` system call.

A pipe is created before the child process is created. After `fork()`, the parent process sends a message through the pipe, and the child process reads and displays that message.

The communication takes place in only one direction.

```text
Parent Process
      │
      │ write()
      │ "hello child!"
      ▼
    PIPE
      │
      │ read()
      ▼
Child Process
```

---

# Working of the Program

The program performs the following steps:

1. Creates a pipe using `pipe()`.
2. Creates a child process using `fork()`.
3. The parent process closes the read end of the pipe.
4. The parent writes a message into the pipe.
5. The child process closes the write end of the pipe.
6. The child reads the message from the pipe.
7. The child displays the received message.
8. Both processes close their respective pipe ends.

---

# Concepts Used

This practical uses the following concepts:

- Inter-Process Communication (IPC)
- Pipes
- Parent and Child Processes
- `fork()` system call
- `pipe()` system call
- `read()` system call
- `write()` system call
- `close()` system call
- File descriptors

---

# Why It Is Called One-Way Communication

This program uses a single pipe.

The parent sends data to the child:

```text
Parent → Child
```

The child receives the message but does not send any response back to the parent.

Therefore, this communication is called:

- One-Way Communication
- Unidirectional Communication

---

# Program File

The source code file used in this practical is:

```text
one_way_pipe.c
```

The program demonstrates:

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

# Compilation

Compile the program using:

```bash
clang one_way_pipe.c -o one_way_pipe
```

### Command Explanation

```text
clang           → C compiler
one_way_pipe.c  → Source code file
-o              → Specifies the output file name
one_way_pipe    → Name of the executable program
```

---

# Execution

Run the program using:

```bash
./one_way_pipe
```

### Command Explanation

```text
./              → Current directory
one_way_pipe    → Executable program
```

---

# Expected Output

The output may appear similar to:

```text
I am in Parent Process
I am in Child Process
Message from parent: hello child!
```

> **Note:** The order of the parent and child process messages may vary because both processes are scheduled independently by the operating system.

---

# Learning Outcome

After completing this practical, the student will understand:

- How a pipe is created using `pipe()`
- How a child process is created using `fork()`
- How the parent process writes data into a pipe
- How the child process reads data from a pipe
- How file descriptors are used for communication
- How one-way IPC works between related processes

---

# Conclusion

This practical successfully demonstrates **one-way Inter-Process Communication using a pipe**.

The final communication flow is:

```text
Parent
   │
   │ write(fd[1])
   ▼
 PIPE
   │
   │ read(fd[0])
   ▼
Child
```

The parent sends information through the pipe, and the child receives and displays the information.