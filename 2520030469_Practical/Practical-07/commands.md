# Operating Systems Lab

# Practical 07 – File Permission Challenge

## Aim

To understand how Linux file permissions affect file access and operations by modifying read, write, and execute permissions using the `chmod` command.

---

## Procedure

### Step 1: Create the directory

**Command**

```bash
mkdir permission_lab
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a new directory named `permission_lab`.

---

### Step 2: Enter the directory

**Command**

```bash
cd permission_lab
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Changes the current working directory to `permission_lab`.

---

### Step 3: Create the file

**Command**

```bash
touch test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates an empty file named `test.txt`.

---

### Step 4: Add content to the file

**Command**

```bash
echo 'This is a test file for permission practice.' > test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Writes sample text into `test.txt`.

---

### Step 5: Display the file contents

**Command**

```bash
cat test.txt
```

**Output**

```text
This is a test file for permission practice.
```

**Explanation**

Displays the contents of `test.txt`.

---

### Step 6: Display the current permissions

**Command**

```bash
ls -l
```

**Output**

```text
Paste your actual terminal output here.
```

**Explanation**

Displays the current permissions of `test.txt`.

---

### Step 7: Remove read permission

**Command**

```bash
chmod u-r test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Removes the read permission for the file owner.

---

### Step 8: Attempt to read the file

**Command**

```bash
cat test.txt
```

**Output**

```text
Paste the actual output displayed on your terminal.
```

**Explanation**

Attempts to display the contents of the file after removing read permission.

---

### Step 9: Restore read permission

**Command**

```bash
chmod u+r test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Restores the read permission for the file owner.

---

### Step 10: Remove write permission

**Command**

```bash
chmod u-w test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Removes the write permission for the file owner.

---

### Step 11: Attempt to modify the file

**Command**

```bash
echo 'Adding new content.' >> test.txt
```

**Output**

```text
Paste the actual output displayed on your terminal.
```

**Explanation**

Attempts to append new content to the file after removing write permission.

---

### Step 12: Restore write permission

**Command**

```bash
chmod u+w test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Restores the write permission for the file owner.

---

### Step 13: Remove execute permission

**Command**

```bash
chmod u-x test.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Removes execute permission from `test.txt`.

---

### Step 14: Attempt to execute the file

**Command**

```bash
./test.txt
```

**Output**

```text
Paste the actual output displayed on your terminal.
```

**Explanation**

Attempts to execute the file after removing execute permission.

---

## Result

Successfully explored the effects of Linux file permissions on file access and operations. The practical demonstrated how read, write, and execute permissions influence the ability to view, modify, and execute files in a Linux environment.