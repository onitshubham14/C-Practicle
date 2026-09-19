# C Practical Programs

A collection of beginner-friendly C programming practicals covering fundamental concepts such as input/output, data types, operators, conditional statements, loops, arrays, searching, sorting, matrices, strings, and basic financial calculations.

This repository is intended for students and beginners who are learning C programming through practical examples.

## 📁 Repository Structure

```text
C-Practicle/
│
├── mini-projects/
│   └── mini-project.c
│
├── shubham-11407/
│   ├── experiment_1.c
│   ├── experiment_2.c
│   ├── experiment_3.c
│   ├── ...
│   └── experiment_19.c
│
└── README.md
```

## 🚀 Getting Started

### Prerequisites

You need a C compiler to compile and run these programs.

The examples in this repository can be compiled using **GCC**.

Check whether GCC is installed:

```bash
gcc --version
```

If GCC is not installed, install a GCC distribution such as MinGW-w64 on Windows or GCC through your system's package manager on Linux/macOS.

---

## 📚 Practical Programs

### 1. Basic C Programs

These programs introduce the basic structure of a C program, output statements, variables, and data types.

| Program          | Description                                                     | Concepts Covered                                         |
| ---------------- | --------------------------------------------------------------- | -------------------------------------------------------- |
| `experiment_1.c` | Prints a simple Hello World message.                            | `main()`, `printf()`, basic C program structure          |
| `experiment_2.c` | Displays basic personal information such as name and age.       | Variables, `printf()`, formatted output                  |
| `experiment_3.c` | Reads two integers and calculates their sum.                    | Variables, `scanf()`, arithmetic operators, input/output |
| `experiment_5.c` | Demonstrates integer, floating-point, and character data types. | `int`, `float`, `char`, format specifiers                |
| `experiment_6.c` | Swaps the values of two numbers using a temporary variable.     | Variables, assignment, temporary variable                |
| `experiment_7.c` | Calculates the area of a circle from its radius. | `float`, input/output, arithmetic operations |

---

### 2. Conditional Statements and Operators

These programs demonstrate decision-making using `if`, `else if`, `else`, logical operators, and `switch`.

| Program           | Description                                                                                 | Concepts Covered                                      |
| ----------------- | ------------------------------------------------------------------------------------------- | ----------------------------------------------------- |
| `experiment_4.c`  | Finds the larger of two numbers.                                                            | `if-else`, relational operators                       |
| `experiment_8.c`  | Determines whether a number is even or odd.                                                 | `if-else`, modulus operator `%`                       |
| `experiment_9.c`  | Finds the maximum among three numbers.                                                      | `if-else-if`, logical operators, relational operators |
| `experiment_10.c` | Performs addition, subtraction, multiplication, or division based on the selected operator. | `switch-case`, arithmetic operators, character input  |

---

### 3. Loops and Control Statements

These programs demonstrate repetition and loop-control statements.

| Program           | Description                                                      | Concepts Covered                |
| ----------------- | ---------------------------------------------------------------- | ------------------------------- |
| `experiment_11.c` | Prints the numbers from 1 to 10.                                 | `for` loop                      |
| `experiment_12.c` | Calculates the sum of integers from 1 to `N`.                    | `for` loop, accumulation        |
| `experiment_13.c` | Demonstrates skipping an iteration and terminating a loop early. | `continue`, `break`, `for` loop |

---

### 4. Arrays and Searching

These programs introduce one-dimensional arrays and basic searching and sorting techniques.

| Program           | Description                                               | Concepts Covered                              |
| ----------------- | --------------------------------------------------------- | --------------------------------------------- |
| `experiment_14.c` | Reads five integers into an array and displays them.      | One-dimensional arrays, loops, array indexing |
| `experiment_15.c` | Searches for a given element in an array.                 | Linear search, arrays, `break`                |
| `experiment_16.c` | Sorts five integers in ascending order using Bubble Sort. | Arrays, nested loops, Bubble Sort, swapping   |

#### Bubble Sort

`experiment_16.c` uses the **Bubble Sort** technique. It repeatedly compares adjacent elements and swaps them when they are in the wrong order.

---

### 5. Matrices

These programs demonstrate two-dimensional arrays and matrix input/output.

| Program           | Description                          | Concepts Covered                     |
| ----------------- | ------------------------------------ | ------------------------------------ |
| `experiment_17.c` | Reads and displays a `2 × 2` matrix. | Two-dimensional arrays, nested loops |
| `experiment_18.c` | Reads and displays a `2 × 2` matrix. | Two-dimensional arrays, nested loops |

> **Note:** `experiment_17.c` and `experiment_18.c` currently contain the same implementation.

---

### 6. Strings

This program demonstrates commonly used functions from the C string library.

| Program           | Description                                                         | Concepts Covered                                                          |
| ----------------- | ------------------------------------------------------------------- | ------------------------------------------------------------------------- |
| `experiment_19.c` | Demonstrates string length, copying, concatenation, and comparison. | Character arrays, strings, `strlen()`, `strcpy()`, `strcat()`, `strcmp()` |

The program uses functions provided by:

```c
#include <string.h>
```

---

## 💰 Mini Project

### Compound Interest Calculator

Location:

```text
mini-projects/mini-project.c
```

This program calculates the final balance of an investment after a specified number of years using annual compound interest.

### Concepts Covered

* Variables and data types
* `float` and `int`
* User input with `scanf()`
* Arithmetic operations
* `for` loop
* Compound interest calculation
* Formatted output

### Formula

For each year, the program calculates:

```text
Interest = Current Balance × Rate / 100
```

and updates the balance:

```text
New Balance = Current Balance + Interest
```

### Example

Input:

```text
Enter principal amount: 10000
Enter rate of interest (in %): 5
Enter number of years: 2
```

Output:

```text
Final balance after 2 years = 11025.00
```

---

# 🛠️ Compilation and Execution

Each C program can be compiled independently using GCC.

## Linux / macOS

Navigate to the directory containing the program:

```bash
gcc experiment_1.c -o experiment_1
```

Run it:

```bash
./experiment_1
```

For example:

```bash
gcc experiment_16.c -o experiment_16
./experiment_16
```

---

## Windows

Using GCC/MinGW:

```powershell
gcc experiment_1.c -o experiment_1.exe
```

Run the executable:

```powershell
.\experiment_1.exe
```

For example:

```powershell
gcc experiment_16.c -o experiment_16.exe
.\experiment_16.exe
```

---

## Compiling the Mini Project

Navigate to the mini-project directory:

```bash
cd mini-projects
```

Compile:

```bash
gcc mini-project.c -o mini-project
```

Run on Linux/macOS:

```bash
./mini-project
```

On Windows:

```powershell
gcc mini-project.c -o mini-project.exe
.\mini-project.exe
```

---

# 🧠 Concepts Covered

The practical programs collectively cover the following C programming concepts:

* C program structure
* `main()` function
* Standard input/output
* `printf()` and `scanf()`
* Variables and constants
* Data types

  * `int`
  * `float`
  * `char`
* Arithmetic operators
* Relational operators
* Logical operators
* Modulus operator
* `if`, `else if`, and `else`
* `switch-case`
* `for` loops
* `break`
* `continue`
* One-dimensional arrays
* Two-dimensional arrays
* Linear search
* Bubble Sort
* Strings
* Standard string library functions
* Nested loops
* Basic financial calculations

---

# 📌 Learning Path

For beginners, the programs can be studied in the following order:

```text
Basic Program Structure
        ↓
Variables & Data Types
        ↓
Input / Output
        ↓
Arithmetic & Operators
        ↓
Conditional Statements
        ↓
Loops
        ↓
Arrays
        ↓
Searching & Sorting
        ↓
Matrices
        ↓
Strings
        ↓
Mini Project
```

This progression starts with basic C syntax and gradually introduces more practical programming concepts.

---

## 🤝 Contributing

Contributions are welcome.

If you would like to improve the examples, documentation, or add new C practical programs:

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Commit your changes.
5. Push the branch.
6. Open a Pull Request.

Please keep new programs beginner-friendly and include appropriate documentation where necessary.

---

## 📄 License

This repository is intended for educational and learning purposes.
