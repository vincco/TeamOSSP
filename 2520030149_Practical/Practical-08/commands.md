# Operating Systems Lab

# Practical 08 – Backup and Restore

## Aim

To understand how to create file backups and restore deleted files using Linux file management commands.

---

## Procedure

### Step 1: Create the directory

**Command**

```bash
mkdir linux_task6
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a new directory named `linux_task6`.

---

### Step 2: Enter the directory

**Command**

```bash
cd linux_task6
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves into the `linux_task6` directory.

---

### Step 3: Create the file

**Command**

```bash
touch important.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates an empty file named `important.txt`.

---

### Step 4: Add content to the file

**Command**

```bash
nano important.txt
```

**Output**

```text
Editor opened successfully.
```

**Explanation**

Adds the required content to `important.txt`.

---

### Step 5: Display the contents of the file

**Command**

```bash
cat important.txt
```

**Output**

```text
Paste your actual file contents here.
```

**Explanation**

Displays the contents stored in `important.txt`.

---

### Step 6: Create the backup directory

**Command**

```bash
mkdir backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a directory named `backup`.

---

### Step 7: Copy the file into the backup directory

**Command**

```bash
cp important.txt backup
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a copy of `important.txt` inside the `backup` directory.

---

### Step 8: Rename the backup file

**Command**

```bash
mv backup/important.txt backup/important_backup.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Renames the copied file to `important_backup.txt`.

---

### Step 9: Delete the original file

**Command**

```bash
rm important.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Deletes the original `important.txt` file.

---

### Step 10: Restore the backup file

**Command**

```bash
cp backup/important_backup.txt .
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Copies the backup file from the `backup` directory into the current directory.

---

### Step 11: Rename the restored file

**Command**

```bash
mv important_backup.txt important_restored.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Renames the restored file to `important_restored.txt`.

---

### Step 12: Display the restored file

**Command**

```bash
cat important_restored.txt
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the contents of the restored file to verify that the backup has been restored successfully.

---

### Step 13: Display the final directory structure

**Command**

```bash
tree
```

**Output**

```text
.
├── backup
│   └── important_backup.txt
└── important_restored.txt

2 directories, 2 files
```

*(Replace with your actual `tree` output if it differs.)*

**Explanation**

Displays the final directory structure after completing the backup and restore process.

---

## Result

Successfully created a backup of a file, restored it after deletion, and verified its contents using Linux file management commands. The practical demonstrated the importance of backups in preventing data loss and recovering information when required.