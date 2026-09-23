# Operating Systems Lab

# Week 3-2 Practical – Process Creation and exec()

## Aim

To understand process creation using `fork()` and process replacement using the `exec()` system call.

---

## Procedure

### Program 1 – factorial.c

#### Step 1: Create the Source File

**Command**

```bash
touch factorial.c
```

**Output**

```text
(No output)
```

**Explanation**

Creates the C source file `factorial.c`, which contains the factorial calculation performed by the child process.

---

#### Step 2: Open the Source File

**Command**

```bash
open -a TextEdit factorial.c
```

**Output**

```text
(TextEdit opens the file)
```

**Explanation**

Opens `factorial.c` so that the program code can be entered and saved.

---

#### Step 3: Compile factorial.c

**Command**

```bash
clang factorial.c -o factorial
```

**Output**

```text
(No output)
```

**Explanation**

Compiles `factorial.c` and creates the executable `factorial`.

---

#### Step 4: Execute factorial

**Command**

```bash
./factorial 5
```

**Output**

```text
--- Child Process (exec) ---
Factorial of 5 = 120
```

**Explanation**

Executes the factorial program with `5` as the command-line argument. The child process calculates the factorial after the `exec()` system call replaces the child process's previous program image.

---

### Program 2 – factorial_square.c

#### Step 5: Open the Parent Program

**Command**

```bash
open -a TextEdit factorial_square.c
```

**Output**

```text
(TextEdit opens the file)
```

**Explanation**

Opens `factorial_square.c`, which creates the child process and executes the separate `factorial` program.

---

#### Step 6: Compile factorial_square.c

**Command**

```bash
clang factorial_square.c -o factorial_square
```

**Output**

```text
(No output)
```

**Explanation**

Compiles `factorial_square.c` and creates the executable `factorial_square`.

---

#### Step 7: Execute factorial_square

**Command**

```bash
./factorial_square
```

**Sample Output**

```text
Enter a number: 5

--- Child Process (exec) ---
Factorial of 5 = 120
--- Parent Process ---
Square of 5 = 25
```

**Explanation**

The program accepts a number, creates a child using `fork()`, and the child uses `exec()` to run the separate `factorial` program. After the child completes, the parent calculates and displays the square of the same number.

---

#### Step 8: Remove the Compiled Executables

**Command**

```bash
rm factorial factorial_square
```

**Output**

```text
(No output)
```

**Explanation**

Removes the compiled executable files while keeping the source programs for submission.

---

## Result

Successfully demonstrated process creation using `fork()` and process replacement using the `exec()` system call. The child process executed a separate factorial program while the parent process calculated the square of the entered number.
