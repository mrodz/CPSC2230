# Makefile Lab

Welcome to the Makefile Lab! In this lab, you'll explore a multi-file C project and learn how compiling, linking, and Makefiles work. This lab is designed to reinforce how Make automates the build process and helps you understand dependency management, the use of automatic variables, and unit testing.

---

## Overview

This project implements a simple math library in C. The library consists of several modules that provide basic mathematical operations:

- **mod.c**: Implements the `mod` function that computes the remainder using repeated subtraction (without the built-in `%` operator).
- **factorial.c**: Implements the `factorial` function recursively. It computes the factorial of a nonnegative integer.
- **power.c**: Implements the `power` function that calculates the base raised to an integer exponent. It supports negative exponents by returning the reciprocal.
- **main.c**: Demonstrates the usage of the math library functions by calling them and printing their results.
- **unittest.c**: Contains unit tests for the math library functions. Each test prints a result line starting with either `PASSED	` or `FAILED	` followed by the test name.

- **Makefile** is intentionally incomplete. Your objective is to complete the targets and dependencies as an exercise in understanding the compiling and linking process.

---

## Objectives

- **Understand Compiling and Linking**:  
  Learn how source files (`.c`) are compiled into object files (`.o`) and how these are linked together to form executables.

- **Learn Makefile Fundamentals**:  
  Understand how Make automates the build process by declaring rules, targets, and dependencies. Complete the Makefile using automatic variables such as `$@` (target) and `$<` (first prerequisite).

- **Practice Incremental Builds**:  
  Explore how Make tracks changes in your source files and only recompiles what is necessary to build the updated executable efficiently.

- **Gain Unit Testing Experience**:  
  Review and run the unit tests provided in **unittest.c**.

---

## Files and Their Roles

- **mathlib.h**:  
  The header file that declares the prototypes for the math functions. All C source files include this header.

- **mod.c**:  
  Implements the `mod` function using repeated subtraction rather than the `%` operator.

- **factorial.c**:  
  Implements the recursive `factorial` function to compute the factorial of a nonnegative integer.

- **power.c**:  
  Implements the `power` function which computes the exponential value for a given base and exponent.

- **main.c**:  
  Demonstrates how to use the math library functions by calling them and printing the results.

- **unittest.c**:  
  Contains unit tests for the above functions. Each test outputs its result with a specific format so that an autograder can process it.

- **Makefile**:  
  An intentionally incomplete Makefile. Your task is to complete the targets and dependencies. The lab objectives include learning the compilation and linking process by using automatic variables like `$@` and `$<`.

---

## Tasks

1. **Review the Source Files**:  
   Open and study each file to understand its functionality:
   - `main.c`
   - `mod.c`
   - `factorial.c`
   - `power.c`
   - `mathlib.h`
   - `unittest.c`

2. **Complete the Makefile**:  
   Fill in the missing targets and dependencies. Use automatic variables:
   - `$@`: Represents the target name.
   - `$<`: Represents the first prerequisite.
   - Ensure that you create rules for:
     - Building the main executable (e.g., `main`)
     - Building the unit test executable (e.g., `test`)
   - Add a `clean` target to remove object files and executables.

3. **Build the Project**:  
   Run the following command to build both executables: `make`

4. **Run the Executables**:
    - Run the main program:`./main` or `make run`
    - Run the unit tests: `./test`

5. **Submit to Gradescope**:
    - Make sure to submit all files to Gradescope before the deadline.

---

## Final Notes
 
- **Building Process**:
Notice how each source file is compiled into an object file and then linked to create the executables. This demonstrates the separation of compilation and linking phases.

- **Incremental Rebuilds**:
Understand how Make detects changes and only rebuilds what is necessary, saving time during development.

---

**Have fun and happy coding!**
