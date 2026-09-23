# Operating Systems Lab

# Practical 03 – Working with head and tail

## Aim

To understand how to view specific portions of a text file using the `head` and `tail` commands in the Linux terminal.

---

## Procedure

### Step 1: Create the directory

**Command**

```bash
mkdir linux_task3
```

**Output**

```text
(No output)
```

**Explanation**

Creates a new directory named `linux_task3`.

---

### Step 2: Verify the directory

**Command**

```bash
ls
```

**Output**

```text
linux_task3
```

**Explanation**

Displays the newly created directory.

---

### Step 3: Enter the directory

**Command**

```bash
cd linux_task3
```

**Output**

```text
(No output)
```

**Explanation**

Moves into the `linux_task3` directory.

---

### Step 4: Create the file

**Command**

```bash
touch students.txt
```

**Output**

```text
(No output)
```

**Explanation**

Creates an empty file named `students.txt`.

---

### Step 5: Add student names

**Command**

```bash
nano students.txt
```

**Output**

```text
(Editor opened)
```

**Explanation**

Adds at least 15 student names, with one name on each line.

---

### Step 6: Display the complete file

**Command**

```bash
cat students.txt
```

**Output**

```text
(Student names displayed)
```

*(Replace this with your actual list of student names.)*

**Explanation**

Displays the complete contents of the file.

---

### Step 7: Display the first five lines

**Command**

```bash
head -5 students.txt
```

**Output**

```text
(First five student names)
```

*(Replace this with your actual output.)*

**Explanation**

Displays the first five lines of the file.

---

### Step 8: Display the first ten lines

**Command**

```bash
head -10 students.txt
```

**Output**

```text
(First ten student names)
```

*(Replace this with your actual output.)*

**Explanation**

Displays the first ten lines of the file.

---

### Step 9: Display the last five lines

**Command**

```bash
tail -5 students.txt
```

**Output**

```text
(Last five student names)
```

*(Replace this with your actual output.)*

**Explanation**

Displays the last five lines of the file.

---

### Step 10: Display the last ten lines

**Command**

```bash
tail -10 students.txt
```

**Output**

```text
(Last ten student names)
```

*(Replace this with your actual output.)*

**Explanation**

Displays the last ten lines of the file.

---

## Result

Successfully created a text file and used the `head` and `tail` commands to view specific sections of its contents. The practical demonstrated how these commands simplify the process of examining large text files in a Linux environment.