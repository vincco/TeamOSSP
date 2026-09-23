# Week 3-2 Practical – Parent and Child Process using fork()

## Aim

To perform and understand process creation using the `fork()` system call, calculate the factorial of a number in the child process, and calculate its square in the parent process.

---

## Program

1. factorial_square.c

---

## Overview

This practical demonstrates process creation using the `fork()` system call. The parent process creates a child process, after which both processes execute independently. The child process calculates the factorial of the given number, while the parent process waits for the child to complete and then calculates the square of the same number. The program also demonstrates the use of `getpid()`, `getppid()`, and `wait()` for process identification and synchronization.