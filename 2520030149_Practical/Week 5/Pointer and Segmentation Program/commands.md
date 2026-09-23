# Commands and Concepts Used – Pointer and Segmentation Program

This document explains the important C statements, operators, functions, and concepts used in `segmentation.c`.

---

# 1. Header File

## `#include <stdio.h>`

This header file provides standard input and output functions.

The program uses:

```c
printf()
```

Example:

```c
printf("x = %d\n", x);
```

---

# 2. The `main()` Function

Program execution begins from:

```c
int main()
```

The `main()` function contains the instructions executed by the program.

---

# 3. Pointer Declaration

The program declares a pointer:

```c
int *ptr = NULL;
```

Here:

```text
int
│
└── Pointer will store the address of an integer variable

*
│
└── Indicates that ptr is a pointer

ptr
│
└── Pointer variable name

NULL
│
└── Initially points to no valid memory location
```

---

# 4. Integer Variable

The program creates:

```c
int x = 25;
```

This stores:

```text
Variable: x
Value:    25
```

---

# 5. Address Operator `&`

The statement:

```c
&x
```

means:

```text
Address of variable x
```

The program assigns the address of `x` to the pointer:

```c
ptr = &x;
```

The relationship is:

```text
x = 25
│
│ Address of x
▼
ptr
```

---

# 6. Pointer Assignment

The statement:

```c
ptr = &x;
```

stores the memory address of `x` inside `ptr`.

Conceptually:

```text
x
│
├── Value: 25
│
└── Address: 0x....

ptr
│
└── Stores address of x
```

---

# 7. Pointer Dereferencing `*`

The operator:

```c
*ptr
```

is called pointer dereferencing.

It accesses the value stored at the memory address contained in `ptr`.

Example:

```c
printf("%d\n", *ptr);
```

Since `ptr` points to `x`:

```text
ptr → address of x

*ptr → value stored in x

*ptr = 25
```

---

# 8. `printf()` Function

The program uses `printf()` to display values.

## Displaying the Value of `x`

```c
printf("x = %d\n", x);
```

Output:

```text
x = 25
```

---

## Displaying the Address of `x`

```c
printf("address of x = %p\n", (void *)&x);
```

`%p` is used to display a memory address.

`(void *)` converts the pointer to a generic pointer type suitable for printing with `%p`.

---

## Displaying the Value Stored in `ptr`

```c
printf("value of ptr = %p\n", (void *)ptr);
```

Since `ptr` stores the address of `x`, this prints the same address as `&x`.

---

## Displaying the Value Pointed to by `ptr`

```c
printf("value pointed by ptr = %d\n", *ptr);
```

This accesses the value stored at the address inside `ptr`.

Output:

```text
value pointed by ptr = 25
```

---

# 9. Format Specifiers

The program uses:

```text
%d
```

For integer values.

Example:

```c
printf("%d", x);
```

The program also uses:

```text
%p
```

For memory addresses.

Example:

```c
printf("%p", (void *)&x);
```

---

# 10. Program Execution Flow

```text
START
  │
  ▼
Create ptr = NULL
  │
  ▼
Create x = 25
  │
  ▼
ptr = &x
  │
  ▼
Print value of x
  │
  ▼
Print address of x
  │
  ▼
Print address stored in ptr
  │
  ▼
Dereference ptr using *ptr
  │
  ▼
Print value 25
  │
  ▼
END
```

---

# 11. Memory Representation

The program can be understood as:

```text
Variable x

+-----------+
|    25     |
+-----------+
      ▲
      │
      │ ptr points here
      │
+----------------+
|      ptr       |
| Address of x   |
+----------------+
```

Therefore:

```text
x       → 25

&x      → Address of x

ptr     → Address of x

*ptr    → 25
```

---

# 12. Compilation Command

Compile the program using:

```bash
clang segmentation.c -o segmentation
```

## Command Breakdown

```text
clang
│
└── C compiler

segmentation.c
│
└── Source code file

-o
│
└── Specifies the output file name

segmentation
│
└── Generated executable
```

---

# 13. Running the Program

Run the compiled program:

```bash
./segmentation
```

The output will be similar to:

```text
x = 25
address of x = 0x...
value of ptr = 0x...
value pointed by ptr = 25
```

The exact memory addresses may change between executions.

---

# 14. `return 0`

The program ends with:

```c
return 0;
```

This indicates successful completion of the `main()` function.

---

# 15. Important Note About Segmentation Faults

Although the file is named:

```text
segmentation.c
```

this program does not produce a segmentation fault.

Initially:

```c
int *ptr = NULL;
```

means the pointer does not point to valid data.

However, before the program uses:

```c
*ptr
```

it executes:

```c
ptr = &x;
```

Therefore, `ptr` contains a valid address.

This makes the dereferencing operation safe:

```c
*ptr
```

---

# 16. Important Concepts Learned

This program demonstrates:

```text
C Program Structure
        ↓
Variables
        ↓
Pointers
        ↓
Memory Addresses
        ↓
Address Operator &
        ↓
Pointer Assignment
        ↓
Dereferencing Operator *
        ↓
Memory Address Printing
```

---

# Conclusion

This program demonstrates how pointers work in C.

The pointer `ptr` stores the address of the variable `x`:

```c
ptr = &x;
```

The value stored at that address is accessed using:

```c
*ptr
```

The program successfully demonstrates the relationship between variables, memory addresses, pointers, and pointer dereferencing.