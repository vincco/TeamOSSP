# Commands and Concepts Used – FIFO Named Pipe Communication

This document explains the important C functions, system calls, constants, commands, and concepts used in the FIFO Named Pipe Communication practical.

---

# 1. Header Files

## `#include <stdio.h>`

This header file provides standard input and output functions.

Used in the programs for:

```c
printf()
```

### Purpose

`printf()` is used to display messages on the terminal.

Example:

```c
printf("Waiting for reader connection...\n");
```

---

## `#include <unistd.h>`

This header file provides access to several UNIX and POSIX system calls.

Used for:

```c
read()
write()
close()
```

### Example

```c
write(fd, msg, strlen(msg));
```

---

## `#include <fcntl.h>`

This header file provides file control options required when opening files or FIFOs.

Used for:

```c
open()
O_RDONLY
O_WRONLY
```

### Access Modes

```text
O_RDONLY → Open for reading only

O_WRONLY → Open for writing only
```

---

## `#include <sys/stat.h>`

This header file provides definitions used for file permissions and FIFO creation.

It is used with:

```c
mkfifo()
```

Example:

```c
mkfifo(path, 0666);
```

---

## `#include <sys/types.h>`

This header file defines various system data types used by UNIX system calls.

It is commonly included when working with:

```text
Files
Pipes
FIFOs
Processes
System calls
```

---

## `#include <string.h>`

This header file provides string handling functions.

Used for:

```c
strlen()
```

Example:

```c
strlen(msg)
```

This calculates the length of the message before writing it to the FIFO.

---

# 2. FIFO Path

The FIFO communication channel uses the following path:

```c
char *path = "/tmp/fifo_pipe";
```

This path represents the named pipe created in the file system.

Both programs must use the same path:

```text
FIFO Writer
      │
      ▼
/tmp/fifo_pipe
      │
      ▼
FIFO Reader
```

If the writer and reader use different paths, communication will not occur.

---

# 3. `mkfifo()` – Creating the Named Pipe

The FIFO is created using:

```c
mkfifo(path, 0666);
```

## Syntax

```c
mkfifo(path, permissions);
```

### Parameters

```text
path
│
└── Location and name of the FIFO


permissions
│
└── Access permissions for the FIFO
```

In this program:

```text
/tmp/fifo_pipe
```

is the FIFO path.

The permission value:

```text
0666
```

allows read and write access according to the process permissions and system rules.

---

# 4. `open()` – Opening the FIFO

The writer opens the FIFO using:

```c
int fd = open(path, O_WRONLY);
```

The reader opens the FIFO using:

```c
int fd = open("/tmp/fifo_pipe", O_RDONLY);
```

## Writer Mode

```c
O_WRONLY
```

Means:

```text
Write Only
```

The writer sends data into the FIFO.

---

## Reader Mode

```c
O_RDONLY
```

Means:

```text
Read Only
```

The reader receives data from the FIFO.

---

# 5. File Descriptor

The value returned by `open()` is stored in:

```c
int fd;
```

`fd` means:

```text
File Descriptor
```

A file descriptor is an integer used by the operating system to identify an open file, pipe, or FIFO.

Example:

```text
fd = 3
```

The file descriptor is later used by:

```c
read()
write()
close()
```

---

# 6. `write()` – Sending Data

The writer sends a message using:

```c
write(fd, msg, strlen(msg));
```

## Syntax

```c
write(file_descriptor, data, number_of_bytes);
```

### In this program

```text
fd
│
└── FIFO file descriptor


msg
│
└── Message to send


strlen(msg)
│
└── Number of characters to write
```

The message travels as:

```text
FIFO Writer
      │
      │ write()
      ▼
/tmp/fifo_pipe
```

---

# 7. `read()` – Receiving Data

The reader receives the message using:

```c
read(fd, bfr, sizeof(bfr));
```

## Syntax

```c
read(file_descriptor, buffer, number_of_bytes);
```

### In this program

```text
fd
│
└── FIFO file descriptor


bfr
│
└── Buffer used to store received data


sizeof(bfr)
│
└── Maximum number of bytes to read
```

The communication flow is:

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

---

# 8. Message Buffer

The reader creates a buffer using:

```c
char bfr[100];
```

This creates a character array capable of storing received data.

Example:

```text
Before receiving:

bfr → Empty


After receiving:

bfr → "Hello receiver!"
```

---

# 9. Message Sent by Writer

The writer stores the message in:

```c
char msg[] = "Hello receiver!\n";
```

This message is sent through the FIFO using:

```c
write(fd, msg, strlen(msg));
```

The reader receives the message and stores it in:

```c
bfr
```

---

# 10. `strlen()` – Finding String Length

The writer uses:

```c
strlen(msg)
```

`strlen()` calculates the number of characters in a string.

Example:

```c
strlen("Hello")
```

returns:

```text
5
```

The returned length is used to tell `write()` how many characters should be sent.

---

# 11. `sizeof()` – Determining Buffer Size

The reader uses:

```c
sizeof(bfr)
```

This determines the total size of the buffer.

Since:

```c
char bfr[100];
```

the expression:

```c
sizeof(bfr)
```

represents the total size available for the buffer.

It is used in:

```c
read(fd, bfr, sizeof(bfr));
```

---

# 12. `close()` – Closing the FIFO

After communication is complete, the file descriptor is closed using:

```c
close(fd);
```

## Purpose

`close()` releases the file descriptor associated with the FIFO.

### Example

```c
close(fd);
```

The communication process is then completed.

---

# 13. `printf()` – Displaying Messages

`printf()` is used to display information to the user.

### Writer Example

```c
printf("Waiting for reader connection...\n");
```

and:

```c
printf("Writer sent a message.\n");
```

### Reader Example

```c
printf("Receiving message from writer...\n");
```

and:

```c
printf("Received message: %s", bfr);
```

---

# 14. FIFO Blocking Behavior

A FIFO is used for communication between processes.

When the writer opens the FIFO using:

```c
open(path, O_WRONLY);
```

it waits until a reader opens the FIFO.

Similarly, when the reader opens the FIFO using:

```c
open(path, O_RDONLY);
```

it waits for communication with the writer.

This creates synchronization between the two programs.

Example:

```text
Writer Started
      │
      ▼
Waiting for Reader
      │
      ▼
Reader Opens FIFO
      │
      ▼
Connection Established
      │
      ▼
Message Transferred
```

---

# 15. Writer Program Commands

The main operations performed by the writer are:

```text
1. Define FIFO path
2. Create FIFO using mkfifo()
3. Display waiting message
4. Open FIFO in write-only mode
5. Write message
6. Display confirmation
7. Close FIFO
```

### Program Flow

```text
START
  │
  ▼
Define Path
  │
  ▼
mkfifo()
  │
  ▼
open() → O_WRONLY
  │
  ▼
write()
  │
  ▼
close()
  │
  ▼
END
```

---

# 16. Reader Program Commands

The main operations performed by the reader are:

```text
1. Create message buffer
2. Display receiving message
3. Open FIFO in read-only mode
4. Read message
5. Display received message
6. Close FIFO
```

### Program Flow

```text
START
  │
  ▼
Create Buffer
  │
  ▼
open() → O_RDONLY
  │
  ▼
read()
  │
  ▼
Display Message
  │
  ▼
close()
  │
  ▼
END
```

---

# 17. Compilation Commands

Compile the writer program:

```bash
clang fifo_writer.c -o fifo_writer
```

### Explanation

```text
clang
│
└── C compiler


fifo_writer.c
│
└── Source code file


-o
│
└── Specifies output file name


fifo_writer
│
└── Generated executable
```

---

Compile the reader program:

```bash
clang fifo_reader.c -o fifo_reader
```

This creates the executable:

```text
fifo_reader
```

---

# 18. Execution Commands

## Terminal 1 – Writer

Run:

```bash
./fifo_writer
```

The writer waits for the reader connection.

---

## Terminal 2 – Reader

Open another Terminal window or tab and navigate to the same directory.

Run:

```bash
./fifo_reader
```

The reader receives the message sent by the writer.

---

# 19. Complete FIFO Communication Flow

```text
START
  │
  ├───────────────────────┐
  │                       │
  ▼                       ▼
FIFO Writer            FIFO Reader
  │                       │
  │ mkfifo()              │
  ▼                       │
/tmp/fifo_pipe            │
  │                       │
  │ open(O_WRONLY)        │ open(O_RDONLY)
  │                       │
  ├──── write() ─────────►│
  │                       │
  │                       │ read()
  │                       ▼
  │                 Store in Buffer
  │                       │
  │                       ▼
  │                 Display Message
  │                       │
  ▼                       ▼
close()                 close()
  │                       │
  └───────────────┬───────┘
                  │
                  ▼
                 END
```

---

# 20. Important Concepts Learned

This practical demonstrates:

```text
Inter-Process Communication
        ↓
FIFO / Named Pipe
        ↓
Separate Processes
        ↓
File Descriptors
        ↓
mkfifo()
        ↓
open()
        ↓
write()
        ↓
read()
        ↓
close()
```

---

# Conclusion

The FIFO Named Pipe Communication practical demonstrates communication between two independent programs.

The writer creates and opens the FIFO, then sends a message using:

```c
write()
```

The reader opens the same FIFO and receives the message using:

```c
read()
```

The FIFO acts as a named communication channel:

```text
Writer
   │
   ▼
Named Pipe
/tmp/fifo_pipe
   │
   ▼
Reader
```

This practical demonstrates an important form of UNIX and Linux Inter-Process Communication.