# Operating Systems Lab

# Practical 09 – Complete Linux File Management Challenge

## Aim

To apply Linux file management commands by creating directories, organizing files, managing permissions, and performing file operations in a single practical exercise.

---

## Procedure

### Step 1: Create the project directory

**Command**

```bash
mkdir linux_project
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
cd linux_project
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves into the `linux_project` directory.

---

### Step 3: Create the required subdirectories

**Command**

```bash
mkdir source backup docs
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the required project directories.

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

Displays the current project directory structure.

---

### Step 5: Create the required files

**Command**

```bash
touch source/main.c source/helper.c source/README.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the required source files inside the `source` directory.

---

### Step 6: Add content to README.txt

**Command**

```bash
nano source/README.txt
```

**Output**

```text
Editor opened successfully.
```

**Explanation**

Adds the required content to `README.txt`.

---

### Step 7: Display the first five lines

**Command**

```bash
head -5 source/README.txt
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the first five lines of the file.

---

### Step 8: Display the last five lines

**Command**

```bash
tail -5 source/README.txt
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the last five lines of the file.

---

### Step 9: Copy main.c to the backup directory

**Command**

```bash
cp source/main.c backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a backup copy of `main.c`.

---

### Step 10: Copy README.txt to the docs directory

**Command**

```bash
cp source/README.txt docs
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Copies `README.txt` into the `docs` directory.

---

### Step 11: Rename helper.c

**Command**

```bash
mv source/helper.c source/functions.c
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Renames `helper.c` to `functions.c`.

---

### Step 12: Change the permission of README.txt

**Command**

```bash
chmod 644 source/README.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Changes the permission of `README.txt` to `644`.

---

### Step 13: Delete the copied main.c

**Command**

```bash
rm backup/main.c
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Deletes the copied `main.c` from the `backup` directory.

---

### Step 14: Verify that the backup directory is empty

**Command**

```bash
ls backup
```

**Output**

```text
(No files listed – the backup directory is empty.)
```

**Explanation**

Confirms that the copied file has been removed successfully.

---

### Step 15: Remove the backup directory

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

### Step 16: Display the final directory structure

**Command**

```bash
tree
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the final project directory structure after completing all file management operations.

---

## Result

Successfully performed a complete Linux file management workflow by creating directories, managing files, modifying permissions, organizing project files, and maintaining the project structure using Linux terminal commands.