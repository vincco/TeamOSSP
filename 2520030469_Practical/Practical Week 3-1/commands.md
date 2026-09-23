# Operating Systems Lab

# Week 3-1 Practical – Process Creation and Process Synchronization

## Aim

To understand process creation and process synchronization using the `fork()`, `sleep()`, and `wait()` system calls.

---

## Procedure

### Program 1 – sleep.c

#### Step 1: Compile the Program

**Command**

```bash
clang sleep.c -o sleep_program
```

**Output**

```text
(No output)
```

**Explanation**

Compiles `sleep.c` and creates the executable file `sleep_program`.

---

#### Step 2: Execute the Program

**Command**

```bash
./sleep_program
```

**Output**

```text
Program Started

(Program waits for 5 seconds)

Program Ended
```

**Explanation**

Runs the program and demonstrates the `sleep()` system call by pausing execution for five seconds before displaying the final message.

---

### Program 2 – forksleep.c

#### Step 3: Compile the Program

**Command**

```bash
clang forksleep.c -o forksleep
```

**Output**

```text
(No output)
```

**Explanation**

Compiles `forksleep.c` and creates the executable `forksleep`.

---

#### Step 4: Execute the Program

**Command**

```bash
./forksleep
```

**Output**

```text
Start of Parent
Start of Child
End of Child
End of Parent
```

**Explanation**

Runs the program and demonstrates process creation using `fork()`. Both parent and child processes execute independently, with `sleep()` delaying their completion.

**Note:** The exact order of process output may vary depending on process scheduling.

---

### Program 3 – waitfork.c

#### Step 5: Compile the Program

**Command**

```bash
clang waitfork.c -o waitfork
```

**Output**

```text
(No output)
```

**Explanation**

Compiles `waitfork.c` and creates the executable `waitfork`.

---

#### Step 6: Execute the Program

**Command**

```bash
./waitfork
```

**Output**

```text
Start of Parent
Start of Child
End of Parent
```

**Explanation**

Runs the program and demonstrates synchronization between the parent and child processes using `wait()`. The child process terminates using `exit(0)` before the statement following `exit(0)` can execute.

---

#### Step 7: Remove the Compiled Executables

**Command**

```bash
rm sleep_program forksleep waitfork
```

**Output**

```text
(No output)
```

**Explanation**

Removes the compiled executable files so that only the source programs and documentation remain in the practical directory.

---

## Result

Successfully compiled and executed programs demonstrating process creation, execution delay, and process synchronization using the `fork()`, `sleep()`, and `wait()` system calls.
