# Linux File Backup and Synchronization System

A menu-driven Linux backup and synchronization project developed in C
using Linux/POSIX system calls.

## Project Overview

The system is designed to back up selected files from a source directory
to a backup location, help keep copies synchronized, and support
periodic backup operations.

The project demonstrates Linux file and directory handling, system
calls, file comparison, backup verification, and command-line
interaction.

## Team Members

  Name       Student ID
  ---------- ------------
  Mahitha    2520030469
  Vineetha   2520030149
  Nityay     2520030618

**Institution:** KLH University, Bachupally\
**Project Guide:** S. Bheekya

## Objectives

-   Develop a Linux file backup system using C.
-   Synchronize files between source and backup locations.
-   Support manual and periodic backup operations.
-   Help verify the integrity of copied files.
-   Provide a command-line menu to access project functions.

## Technologies

-   C programming
-   Ubuntu/Linux
-   GCC compiler
-   Linux/POSIX file and directory operations

## System Calls and Functions

The project presentation identifies the following calls and functions:

  Function      Purpose
  ------------- -------------------------
  `open()`      Open a file
  `read()`      Read file data
  `write()`     Write file data
  `stat()`      Retrieve file metadata
  `chmod()`     Change file permissions
  `opendir()`   Open a directory
  `readdir()`   Read directory entries

Use only the functions implemented in the submitted source code when
describing the final implementation.

## Workflow

1.  Select or configure a source directory.
2.  Scan files in the source directory.
3.  Compare file information to identify new or modified files.
4.  Copy the required files to the backup destination.
5.  Verify copied data, where checksum verification is implemented.
6.  Repeat the process manually or on a schedule, depending on the
    selected mode.

## Menu Features

The application menu is intended to provide options for:

1.  Manual synchronization
2.  Start automatic backup
3.  Stop automatic backup
4.  View source files
5.  View backup files
6.  View file information
7.  View activity log
8.  View backup statistics
9.  Exit

The exact behavior of each option depends on the current implementation
in the source code.

## Requirements

-   Ubuntu or another Linux environment
-   GCC compiler
-   Terminal access
-   Read/write permissions for the source and backup directories

## Build and Run

From the project directory, compile the main C source file:

``` bash
gcc main.c -o main
```

Run the application:

``` bash
./main
```

If your source file or executable has a different name, replace `main.c`
or `main` accordingly.

## Example Backup Verification

If the project uses `source` and `backup` directories, you can compare a
file with:

``` bash
diff source/test.txt backup/test.txt
```

You can also compare checksums:

``` bash
md5sum source/test.txt backup/test.txt
```

Matching checksums indicate matching file contents for this check. MD5
is not recommended for security-sensitive integrity verification.

## Project Structure

The directory names below are illustrative. Adjust them to match the
actual repository:

``` text
LinuxBackup/
├── main.c
├── source/
├── backup/
├── README.md
└── ...
```

## Notes

-   Ensure the source and backup directory paths match the paths
    expected by the program.
-   Do not commit private data or files that should not be shared.
-   Confirm which features are implemented and tested before presenting
    them as completed.

## Acknowledgement

We thank our project guide, S. Bheekya, and KLH University, Bachupally,
for their guidance and support.
