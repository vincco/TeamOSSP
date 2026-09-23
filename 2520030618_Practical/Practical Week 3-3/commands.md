# Operating Systems Lab

# Week 3-3 Practical – Process State Transitions

## Aim

To observe process execution and understand the transitions between process states using process monitoring commands.

---

## Procedure

### Step 1: Compile the Process State Program

**Command**

```bash
clang process_state.c -o process_state
```

**Output**

```text
(No output)
```

**Explanation**

Compiles `process_state.c` and creates the executable `process_state`.

---

### Step 2: Execute the Program

**Command**

```bash
./process_state
```

**Sample Output**

```text
Parent Process Started

--- Parent Process ---
Parent PID : 48568
Parent waiting for child...

--- Child Process ---
Child PID : 48569
Parent PID : 48568
Child is running...

Child Process Finished
Parent Process Finished
```

**Explanation**

Runs the program and demonstrates the interaction between the parent and child processes. The process IDs shown in the output may differ each time the program is executed.

---

### Step 3: Display Active Processes

**Command**

```bash
ps
```

**Output**

```text
(Active processes are displayed)
```

**Explanation**

Displays information about currently running processes. It can be used to observe process IDs and process execution status from the terminal.

---

### Step 4: Monitor Processes

**Command**

```bash
top
```

**Output**

```text
(Real-time process information is displayed)
```

**Explanation**

Displays continuously updated information about running processes and system activity. It can be used to observe processes while they are executing.

Press `q` to exit `top`.

---

### Step 5: Remove the Compiled Executable

**Command**

```bash
rm process_state
```

**Output**

```text
(No output)
```

**Explanation**

Removes the compiled executable after completing the process-state observation.

---

## Result

Successfully compiled and executed the process-state program and used process-monitoring commands to observe running processes and their execution behavior.
