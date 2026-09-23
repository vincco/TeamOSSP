# Pointer and Segmentation Program

## Objective

To demonstrate the use of pointers in C, including storing a variable's address and accessing its value through a pointer.

---

## Program Description

The program creates:

- An integer variable `x`
- A pointer `ptr`
- The pointer is assigned the address of `x`
- The program displays:
  - Value of `x`
  - Address of `x`
  - Value stored in `ptr`
  - Value accessed using `*ptr`

---

## Pointer Concept

```text
x = 25
│
│ Address of x
▼
ptr
│
│ Dereference using *ptr
▼
25
```

The statement:

```c
ptr = &x;
```

stores the address of `x` inside `ptr`.

The statement:

```c
*ptr
```

accesses the value stored at that address.

---

## Program Flow

```text
START
  │
  ▼
Create pointer ptr
  │
  ▼
Create variable x = 25
  │
  ▼
Assign address of x to ptr
  │
  ▼
Display x
  │
  ▼
Display address of x
  │
  ▼
Display value of ptr
  │
  ▼
Display value using *ptr
  │
  ▼
END
```

---

## Compilation

```bash
clang segmentation.c -o segmentation
```

---

## Execution

```bash
./segmentation
```

---

## Expected Output

```text
x = 25
address of x = 0x...
value of ptr = 0x...
value pointed by ptr = 25
```

The memory addresses will be different on different systems and executions.

---

## Important Note

Although the file is named `segmentation.c`, this program does not cause a segmentation fault because:

```c
ptr = &x;
```

assigns a valid memory address to the pointer before it is dereferenced.

---

## Conclusion

This program demonstrates pointer operations in C, including:

```text
Pointer declaration
Address operator &
Pointer assignment
Pointer dereferencing *
Memory address printing
```