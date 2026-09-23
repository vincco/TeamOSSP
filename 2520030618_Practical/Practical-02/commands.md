# Operating Systems Lab

# Practical 02 – Copy and Move Files

## Aim

To understand the Linux file management commands used for copying, moving, and renaming files and directories through the terminal.

---

## Execution

### Step 1: Create the directory

**Command**

```bash
mkdir linux_task2
```

**Output**

```text
(No output)
```

**Explanation**

Creates a new directory named `linux_task2`.

---

### Step 2: Verify the directory

**Command**

```bash
ls
```

**Output**

```text
linux_task2
```

**Explanation**

Lists the contents of the current directory to verify that `linux_task2` has been created.

---

### Step 3: Enter the directory

**Command**

```bash
cd linux_task2
```

**Output**

```text
(No output)
```

**Explanation**

Changes the current working directory to `linux_task2`.

---

### Step 4: Create the required files

**Command**

```bash
touch source.txt data.txt notes.txt
```

**Output**

```text
(No output)
```

**Explanation**

Creates three empty text files.

---

### Step 5: Display the files

**Command**

```bash
ls
```

**Output**

```text
data.txt
notes.txt
source.txt
```

**Explanation**

Lists all files present in the directory.

---

### Step 6: Add content to source.txt

**Command**

```bash
echo 'This is the source file.' > source.txt
```

**Output**

```text
(No output)
```

**Explanation**

Writes sample text into `source.txt`.

---

### Step 7: Display the contents of source.txt

**Command**

```bash
cat source.txt
```

**Output**

```text
This is the source file.
```

**Explanation**

Displays the contents of `source.txt`.

---

### Step 8: Create the backup directory

**Command**

```bash
mkdir backup
```

**Output**

```text
(No output)
```

**Explanation**

Creates a directory named `backup`.

---

### Step 9: Copy source.txt to the backup directory

**Command**

```bash
cp source.txt backup
```

**Output**

```text
(No output)
```

**Explanation**

Creates a copy of `source.txt` inside the `backup` directory.

---

### Step 10: Verify the copied file

**Command**

```bash
ls backup
```

**Output**

```text
source.txt
```

**Explanation**

Confirms that `source.txt` has been copied successfully.

---

### Step 11: Copy and rename data.txt

**Command**

```bash
cp data.txt backup/data_backup.txt
```

**Output**

```text
(No output)
```

**Explanation**

Copies `data.txt` into the `backup` directory and renames it as `data_backup.txt`.

---

### Step 12: Verify the backup directory

**Command**

```bash
ls backup
```

**Output**

```text
data_backup.txt
source.txt
```

**Explanation**

Displays the files currently stored in the `backup` directory.

---

### Step 13: Move notes.txt to the backup directory

**Command**

```bash
mv notes.txt backup
```

**Output**

```text
(No output)
```

**Explanation**

Moves `notes.txt` into the `backup` directory.

---

### Step 14: Display the current directory

**Command**

```bash
ls
```

**Output**

```text
backup
data.txt
source.txt
```

**Explanation**

Displays the remaining files and directories in the current directory.

---

### Step 15: Rename source.txt

**Command**

```bash
mv source.txt original.txt
```

**Output**

```text
(No output)
```

**Explanation**

Renames `source.txt` to `original.txt`.

---

### Step 16: Display the updated directory

**Command**

```bash
ls
```

**Output**

```text
backup
data.txt
original.txt
```

**Explanation**

Verifies that the file has been renamed successfully.

---

### Step 17: Display the final directory structure

**Command**

```bash
tree
```

**Output**

```text
.
├── backup
│   ├── data_backup.txt
│   ├── notes.txt
│   └── source.txt
├── data.txt
└── original.txt

2 directories, 5 files
```

**Explanation**

Displays the complete directory structure after performing all file operations.

---

## Result

Successfully copied, moved, and renamed files using Linux terminal commands. The practical demonstrated efficient file organization and directory management through command-line operations.