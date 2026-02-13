# Lab 3 : Hookbook

> **Edit ONLY `PirateList.c`.**  
> Do not modify `PirateList.h`, `main.c`, `unittest.c`, `Makefile`, or `pirate_names.txt`.

---

## Lab Description

Your mission is to maintain a **hookbook** of pirates by **reading names from a text file** and storing them in a fixed-size array-backed list. You’ll practice arrays, structs, basic file I/O, and clean modular design in C.

---

## Learning Objectives

1. Practice working with **static arrays** and **structs**.  
2. Learn **file I/O** using `FILE*` and `fgets`.  
3. Implement modular code split across `.c` and `.h` files.  
4. Run and interpret simple **unit tests**.

---

## Repository Layout (starter files)

- `PirateList.h` – Type definitions and function prototypes for the pirate list.  
- `PirateList.c` – **Your task**: implement the three functions described below.  
- `main.c` – A small driver that opens `pirate_names.txt`, loads pirates, and prints the list.  
- `pirate_names.txt` – Sample input file (one pirate name per line).  
- `unittest.c` – Unit tests for your implementation.  
- `Makefile` – Builds the main program (`hookbook`) and the tests (`test`).

> **Important:** Students should **only edit `PirateList.c`**.

---

## What you must implement (in `PirateList.c`)

Implement **exactly these functions** to satisfy the driver and unit tests:

### 1) `void piratelist_init(List *list)`
- Set the list to an empty state.  

### 2) `int piratelist_add(List *list, FILE *file)`
Read **all** lines from the given `file` and append them to the list **until** the file ends or the list reaches capacity.

**Requirements enforced by tests:**
- Use a fixed buffer of size `LINE_MAX` (already defined). Read with `fgets`.  
- Assign each pirate a sequential ID starting at **1**, in insertion order. (So the first pirate has `pirate_id == 1`, the second `2`, etc.)  
- If you run out of capacity (`MAX_PIRATES`) while reading, stop inserting and **return `0`**.  
- If you finish reading without hitting capacity, **return `1`** (even if the file was empty).  
- **Try/Experiment** to write past the array bounds.
- Change the array size to a smaller number (**<10**) and see if your code behaves correctly.

### 3) `void piratelist_print(const List *list)`
- Iterate over the list and print each pirate.  
- Include at least the **ID** and **name** on each line.

---

## Types and limits (from `PirateList.h`)

- `#define MAX_PIRATES 10` – the fixed capacity of the list.  
- `#define LINE_MAX 128` – buffer size for reading lines.  
- `typedef struct { int pirate_id; char name[LINE_MAX]; } Pirate;`  
- `typedef struct { int length; Pirate pirates[MAX_PIRATES]; } List;`

---

## Build, Run, Test

```bash
# Build everything (main program + tests)
make

# Run the main program (loads from pirate_names.txt and prints)
./hookbook

# Or use the convenience target:
make run

# Build the tests (usually built by `make` already) and run them
make test
./test

# Clean build outputs
make clean
```

---

## Hints & Pitfalls

- Use `while (fgets(line, sizeof line, file) != NULL) { ... }`.  
- Insert at index `list->length` and then increment it.  
- Check capacity **before** copying into the array.  
- Names already include a newline; don’t add another `\n` when printing the name directly.  
- Do not allocate dynamic memory for this lab.

---

## Submission

Submit your **entire project** to Gradescope, but ensure that your changes are **only** in `PirateList.c`. The autograder will compile and run the unit tests. Aim for **no warnings** under the provided flags: `-Wall -Wextra -std=c99 -pedantic -g`.

---

## Reflection Questions (turn in short answers)

1. What is the biggest limitation of this program’s design?  
2. Is defining the `struct` in the header a good idea?

---
