# Practical 06 – File Permissions Using chmod

## Aim

To understand Linux file permissions and learn how to modify them using the `chmod` command.

---

## Problem Statement

### Task 6: File Permissions Using chmod

**Objective:** Understand Linux file permissions.

### Instructions

1. Create a directory called `linux_task4`.
2. Create three files:
   - `public.txt`
   - `private.txt`
   - `script.sh`
3. Add some content to each file.
4. Display the current permissions using `ls -l`.
5. Set `private.txt` permission to `600`.
6. Set `public.txt` permission to `644`.
7. Give execute permission to `script.sh`.
8. Check the permissions again.
9. Remove execute permission from `script.sh`.

---

## Overview

Linux uses a permission-based security model to control access to files and directories. The `chmod` command allows users to modify file permissions by granting or removing read, write, and execute privileges. This practical demonstrates how different permission settings affect file accessibility and execution.