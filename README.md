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
## 🌍 Real-World Applications and Implementations

The Linux File Backup and Synchronization System is based on concepts widely used in enterprise storage systems, data centers, cloud platforms, educational institutions, and software development environments.

The following are practical real-world applications of the system.

### 1. Healthcare and Hospital Data Management

**Problem:** Hospitals maintain critical patient information, medical reports, prescriptions, diagnostic images, and electronic health records. Hardware failures or accidental deletion can result in data loss.

**Real-World Implementation:**
- Maintain backup copies of patient records on separate storage servers.
- Use incremental backups to copy only newly created or modified records.
- Perform checksum verification to detect data corruption.
- Schedule automated backups during low-usage hours.
- Maintain off-site backups for disaster recovery.

**Relevant Concepts:** File handling, incremental backup, system calls, data integrity, and automated scheduling.

### 2. Banking and Financial Institutions

**Problem:** Banking systems generate transaction logs, financial reports, audit records, and other critical information that must remain available and protected.

**Real-World Implementation:**
- Periodically back up transaction logs and financial records.
- Maintain multiple backup destinations.
- Verify copied data using checksum mechanisms.
- Implement access permissions to restrict unauthorized file modifications.
- Use locking mechanisms to prevent concurrent backup operations from interfering with each other.

**Relevant Concepts:** File synchronization, data integrity, file permissions, process synchronization, and error handling.

### 3. Universities and Educational Institutions

**Problem:** Universities store student records, attendance information, examination results, assignment submissions, and administrative documents.

**Real-World Implementation:**
- Automatically back up student and examination records.
- Detect modified files using metadata comparison.
- Synchronize backup copies across different storage locations.
- Schedule daily or weekly backup operations.
- Maintain logs of successful and unsuccessful backup operations.

**Relevant Concepts:** Directory traversal, file metadata, incremental backup, scheduling, and logging.

### 4. Software Development and IT Companies

**Problem:** Development teams continuously modify source code, configuration files, project documentation, and application resources.

**Real-World Implementation:**
- Back up important project directories.
- Identify newly created and modified files.
- Copy only changed files to reduce unnecessary disk operations.
- Maintain backup copies on local and remote storage.
- Verify copied files to ensure data consistency.

**Relevant Concepts:** Directory scanning, file comparison, incremental synchronization, and checksum verification.

### 5. Cloud Storage and Distributed File Systems

**Problem:** Cloud storage platforms need to maintain consistent copies of files across storage servers and connected devices.

**Real-World Implementation:**
- Detect changes in files and directories.
- Transfer updated files to remote storage.
- Maintain multiple copies for availability and recovery.
- Verify transferred data.
- Handle network failures and retry unsuccessful transfers.

**Relevant Concepts:** File synchronization, distributed storage, data integrity, error handling, and concurrent operations.

---

## 🛠️ Existing Industry Tools Based on Similar Concepts

The project demonstrates fundamental concepts that are also used in established Linux backup and synchronization utilities.

| Tool | Real-World Purpose | Connection to This Project |
|---|---|---|
| **rsync** | Synchronizes files between local and remote systems. | File comparison and incremental transfer. |
| **Cron** | Executes scheduled tasks automatically. | Periodic backup execution. |
| **BorgBackup** | Provides compressed, deduplicated and encrypted backups. | Efficient backup storage and data protection. |
| **Restic** | Provides secure backups to local and remote storage. | Backup verification and remote storage. |

## 🔧 Practical Implementation Scenarios

The following scenarios can be used to demonstrate the system:

| Scenario | Demonstration | Expected Result |
|---|---|---|
| File Modification | Modify an existing source file. | Only the modified file is backed up. |
| New File Creation | Add a new file to the source directory. | The new file is detected and copied. |
| Data Integrity | Modify a backup copy and compare checksums. | A checksum mismatch is detected. |
| Multiple Destinations | Configure two backup directories. | Both destinations receive updated files. |
| Automated Backup | Configure a scheduled execution. | Backups run automatically. |
| File Permissions | Change source file permissions. | Permission changes can be detected and handled. |
| Backup Failure | Make a destination unavailable. | An error is reported and the operation can be retried. |

## 🚀 Future Real-World Enhancements

The system can be extended with additional capabilities to make it more suitable for enterprise environments:

- **Remote Backup Support:** Transfer files to remote Linux servers using SSH.
- **Encryption:** Protect sensitive backup data using encryption.
- **Versioned Backups:** Preserve previous file versions for recovery.
- **Real-Time Synchronization:** Detect file changes using Linux inotify.
- **Concurrency Control:** Implement mutexes or file locks to prevent simultaneous backup conflicts.
- **Cloud Integration:** Extend backup destinations to cloud storage platforms.
- **Backup Restoration:** Allow users to restore files from previous backups.
- **Monitoring and Notifications:** Generate alerts for failed or completed backup operations.

**Note:** These applications describe potential real-world uses of the project's underlying concepts. They do not imply that the current implementation already includes enterprise features such as encryption, cloud integration, or remote backup.
