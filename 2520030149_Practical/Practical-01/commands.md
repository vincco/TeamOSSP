# Operating Systems Lab

# Practical 01 – Create and Manage Files

## Aim

To understand the basic Linux file management operations by creating, viewing, modifying, and deleting files using terminal commands.

---

## Execution

### Step 1: Create the directory

**Command**

```bash
mkdir linux_task1
```

**Output**

```text
(No output)
```

**Explanation**

Creates a new directory named `linux_task1`.

---

### Step 2: Verify the directory

**Command**

```bash
ls
```

**Output**

```text
linux_task1
```

**Explanation**

Lists the contents of the current directory to confirm that the new directory has been created.

---

### Step 3: Enter the directory

**Command**

```bash
cd linux_task1
```

**Output**

```text
(No output)
```

**Explanation**

Changes the current working directory to `linux_task1`.

---

### Step 4: Verify the current working directory

**Command**

```bash
pwd
```

**Output**

```text
/Users/poojithamusunuri/Documents/OS/Practical-01/linux_task1
```

**Explanation**

Displays the absolute path of the current working directory.

---

### Step 5: Create five empty files

**Command**

```bash
touch file1.txt file2.txt file3.txt file4.txt file5.txt
```

**Output**

```text
(No output)
```

**Explanation**

Creates five empty text files.

---

### Step 6: Display all files

**Command**

```bash
ls
```

**Output**

```text
file1.txt
file2.txt
file3.txt
file4.txt
file5.txt
```

**Explanation**

Lists all files present in the directory.

---

### Step 7: Display detailed file information

**Command**

```bash
ls -l
```

**Output**

```text
total 0
-rw-r--r--  1 poojithamusunuri  staff  0  6 Aug 08:36 file1.txt
-rw-r--r--  1 poojithamusunuri  staff  0  6 Aug 08:36 file2.txt
-rw-r--r--  1 poojithamusunuri  staff  0  6 Aug 08:36 file3.txt
-rw-r--r--  1 poojithamusunuri  staff  0  6 Aug 08:36 file4.txt
-rw-r--r--  1 poojithamusunuri  staff  0  6 Aug 08:36 file5.txt
```

**Explanation**

Displays detailed information about each file, including permissions, owner, size, and modification date.

---

### Step 8: Add content to file1.txt

**Command**

```bash
echo 'Operating Systems Practical 1' > file1.txt
```

**Output**

```text
(No output)
```

**Explanation**

Writes the specified text into `file1.txt`.

---

### Step 9: Display the contents of file1.txt

**Command**

```bash
cat file1.txt
```

**Output**

```text
Operating Systems Practical 1
```

**Explanation**

Displays the contents stored in `file1.txt`.

---

### Step 10: Delete file5.txt

**Command**

```bash
rm file5.txt
```

**Output**

```text
(No output)
```

**Explanation**

Deletes `file5.txt` from the directory.

---

### Step 11: Display the remaining files

**Command**

```bash
ls
```

**Output**

```text
file1.txt
file2.txt
file3.txt
file4.txt
```

**Explanation**

Confirms that `file5.txt` has been successfully deleted.

---

## Result

Successfully created, viewed, modified, and deleted files using Linux terminal commands. The practical demonstrated the basic file management operations required to work with files and directories in a Linux environment.