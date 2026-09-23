# Operating Systems Lab

# Practical 06 – File Permissions Using chmod

## Aim

To understand Linux file permissions and learn how to modify them using the `chmod` command.

---

## Procedure

### Step 1: Create the directory

**Command**

```bash
mkdir linux_task4
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a new directory named `linux_task4`.

---

### Step 2: Enter the directory

**Command**

```bash
cd linux_task4
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves into the `linux_task4` directory.

---

### Step 3: Create the required files

**Command**

```bash
touch public.txt private.txt script.sh
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the required text files and shell script.

---

### Step 4: Add content to the files

**Commands**

```bash
echo 'This is a public file.' > public.txt
echo 'This is a private file.' > private.txt
echo 'echo Hello, Operating Systems!' > script.sh
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Writes sample content into each file.

---

### Step 5: Display the contents of the files

**Commands**

```bash
cat public.txt
cat private.txt
cat script.sh
```

**Output**

```text
This is a public file.

This is a private file.

echo Hello, Operating Systems!
```

**Explanation**

Displays the contents of all three files.

---

### Step 6: Display the current file permissions

**Command**

```bash
ls -l
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the current permissions, owner, size, and modification details of the files.

---

### Step 7: Set the permission of private.txt to 600

**Command**

```bash
chmod 600 private.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Allows only the file owner to read and write the file.

---

### Step 8: Set the permission of public.txt to 644

**Command**

```bash
chmod 644 public.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Allows the owner to read and write the file, while group members and others have read-only access.

---

### Step 9: Grant execute permission to script.sh

**Command**

```bash
chmod +x script.sh
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Adds execute permission to the shell script.

---

### Step 10: Verify the updated permissions

**Command**

```bash
ls -l
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the updated permissions after applying the `chmod` commands.

---

### Step 11: Remove execute permission from script.sh

**Command**

```bash
chmod -x script.sh
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Removes execute permission from the shell script.

---

### Step 12: Verify the final permissions

**Command**

```bash
ls -l
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Confirms that the execute permission has been removed successfully.

---

## Result

Successfully created files and modified their permissions using the `chmod` command. The practical demonstrated how Linux controls file access through read, write, and execute permissions, and how these permissions can be managed from the terminal.