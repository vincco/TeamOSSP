# Operating Systems Lab

# Practical 05 – Directory Management

## Aim

To understand how to create, organize, and manage nested directories and files in Linux using terminal commands.

---

## Procedure

### Step 1: Create the project directory

**Command**

```bash
mkdir project
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the main project directory.

---

### Step 2: Enter the project directory

**Command**

```bash
cd project
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Changes the current working directory to `project`.

---

### Step 3: Create the required subdirectories

**Command**

```bash
mkdir -p source/c source/python docs backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the required nested directory structure.

---

### Step 4: Create three files inside source/c

**Command**

```bash
touch source/c/file1.c source/c/file2.c source/c/file3.c
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates three C source files inside the `source/c` directory.

---

### Step 5: Create two files inside source/python

**Command**

```bash
touch source/python/file1.py source/python/file2.py
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates two Python files inside the `source/python` directory.

---

### Step 6: Display the complete directory structure

**Command**

```bash
tree
```

**Output**

```text
.
├── backup
├── docs
└── source
    ├── c
    │   ├── file1.c
    │   ├── file2.c
    │   └── file3.c
    └── python
        ├── file1.py
        └── file2.py

5 directories, 5 files
```

**Explanation**

Displays the complete project directory structure.

---

### Step 7: Remove the empty backup directory

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

### Step 8: Recreate the backup directory

**Command**

```bash
mkdir backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Recreates the `backup` directory for the next steps.

---

### Step 9: Create a file inside backup

**Command**

```bash
touch backup/backup.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a file inside the `backup` directory.

---

### Step 10: Attempt to remove backup using rmdir

**Command**

```bash
rmdir backup
```

**Output**

```text
rmdir: backup: Directory not empty
```

*(Your terminal wording may vary slightly.)*

**Explanation**

The `rmdir` command cannot remove a directory that contains files.

---

### Step 11: Delete the file inside backup

**Command**

```bash
rm backup/backup.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Deletes the file stored inside the `backup` directory.

---

### Step 12: Remove the backup directory

**Command**

```bash
rmdir backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Removes the now-empty `backup` directory successfully.

---

### Step 13: Display the final directory structure

**Command**

```bash
tree
```

**Output**

```text
.
├── docs
└── source
    ├── c
    │   ├── file1.c
    │   ├── file2.c
    │   └── file3.c
    └── python
        ├── file1.py
        └── file2.py

4 directories, 5 files
```

**Explanation**

Displays the final project structure after removing the `backup` directory.

---

## Result

Successfully created and managed nested directories and files using Linux terminal commands. The practical demonstrated directory creation, file organization, directory removal, and the behavior of the `rmdir` command when attempting to remove a non-empty directory.