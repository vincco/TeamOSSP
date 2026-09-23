# Operating Systems Lab

# Practical 04 – Organize Files

## Aim

To understand how to organize files into different directories by moving and renaming them using Linux terminal commands.

---

## Procedure

### Step 1: Create the main directory

**Command**

```bash
mkdir organization
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates the main directory named `organization`.

---

### Step 2: Enter the directory

**Command**

```bash
cd organization
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves into the `organization` directory.

---

### Step 3: Create the required files

**Command**

```bash
touch file1.txt file2.txt file3.txt image1.jpg image2.jpg
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates three text files and two image files.

---

### Step 4: Display the files

**Command**

```bash
ls
```

**Output**

```text
file1.txt
file2.txt
file3.txt
image1.jpg
image2.jpg
```

**Explanation**

Lists all the newly created files.

---

### Step 5: Create the documents directory

**Command**

```bash
mkdir documents
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a directory to store text files.

---

### Step 6: Create the images directory

**Command**

```bash
mkdir images
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Creates a directory to store image files.

---

### Step 7: Move all text files

**Command**

```bash
mv *.txt documents
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves all text files into the `documents` directory.

---

### Step 8: Move all image files

**Command**

```bash
mv *.jpg images
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Moves all image files into the `images` directory.

---

### Step 9: Display the contents of the documents directory

**Command**

```bash
ls documents
```

**Output**

```text
file1.txt
file2.txt
file3.txt
```

**Explanation**

Displays all text files stored in the `documents` directory.

---

### Step 10: Display the contents of the images directory

**Command**

```bash
ls images
```

**Output**

```text
image1.jpg
image2.jpg
```

**Explanation**

Displays all image files stored in the `images` directory.

---

### Step 11: Rename file1.txt

**Command**

```bash
mv documents/file1.txt documents/notes.txt
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Renames `file1.txt` to `notes.txt`.

---

### Step 12: Rename image1.jpg

**Command**

```bash
mv images/image1.jpg images/photo.jpg
```

**Output**

```text
No output (command executed successfully).
```

**Explanation**

Renames `image1.jpg` to `photo.jpg`.

---

### Step 13: Display the final directory structure

**Command**

```bash
tree
```

**Output**

```text
.
├── documents
│   ├── file2.txt
│   ├── file3.txt
│   └── notes.txt
└── images
    ├── image2.jpg
    └── photo.jpg

2 directories, 5 files
```

**Explanation**

Displays the final organized directory structure after moving and renaming the files.

---

## Result

Successfully organized files into separate directories using the `mv` command and renamed selected files. The practical demonstrated effective file organization and directory management using Linux terminal commands.