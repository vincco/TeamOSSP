# Operating Systems Lab

# Practical 10 – Mini Linux Administration Challenge

## Aim

To perform and understand Linux file administration by organizing project files, managing directories, modifying file permissions, creating backups, and maintaining a structured project using Linux terminal commands.

---

## Procedure

### Step 1: Create the project directory

**Command**

```bash
mkdir student_portal
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the main project directory named `student_portal`.

---

### Step 2: Enter the project directory

**Command**

```bash
cd student_portal
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves into the `student_portal` directory.

---

### Step 3: Create the required subdirectories

**Command**

```bash
mkdir src docs backup logs config
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the required project subdirectories.

---

### Step 4: Display the directory structure

**Command**

```bash
tree
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the initial directory structure.

---

### Step 5: Create the required files

**Command**

```bash
touch main.c student.c README.txt config.txt system.log
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the required project files.

---

### Step 6: Organize the files

**Commands**

```bash
mv main.c student.c src
mv README.txt docs
mv config.txt config
mv system.log logs
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves each file into its respective directory.

---

### Step 7: Display the updated directory structure

**Command**

```bash
tree
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Verifies that all files have been placed in the correct directories.

---

### Step 8: Add content to system.log

**Command**

```bash
nano logs/system.log
```

**Output**

```text
Editor opened successfully.
```

**Explanation**

Adds the required log entries to `system.log`.

---

### Step 9: Display the first five lines

**Command**

```bash
head -5 logs/system.log
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the first five lines of the log file.

---

### Step 10: Display the last five lines

**Command**

```bash
tail -5 logs/system.log
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the last five lines of the log file.

---

### Step 11: Copy README.txt to the backup directory

**Command**

```bash
cp docs/README.txt backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a backup copy of `README.txt`.

---

### Step 12: Rename the backup file

**Command**

```bash
mv backup/README.txt backup/README_backup.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Renames the copied file to `README_backup.txt`.

---

### Step 13: Change the permission of config.txt

**Command**

```bash
chmod 600 config/config.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Sets the permissions of `config.txt` to `600`, allowing only the owner to read and write the file.

---

### Step 14: Change the permission of README.txt

**Command**

```bash
chmod 644 docs/README.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Sets the permissions of `README.txt` to `644`, allowing the owner to read and write the file while others have read-only access.

---

### Step 15: Delete the backup file

**Command**

```bash
rm backup/README_backup.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Deletes the backup copy of `README.txt`.

---

### Step 16: Verify that the backup directory is empty

**Command**

```bash
ls backup
```

**Output**

```text
(No files listed – the backup directory is empty.)
```

**Explanation**

Confirms that the backup directory is empty after deleting the backup file.

---

### Step 17: Remove the backup directory

**Command**

```bash
rmdir backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Removes the empty `backup` directory.

---

### Step 18: Display the final directory structure

**Command**

```bash
ls -R
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the complete project directory structure recursively.

---

## Result

Successfully completed a Linux administration workflow by creating and organizing project directories, managing files, modifying permissions, maintaining backups, and verifying the final project structure using Linux terminal commands.