# Student Grade Management System – C Mini Project

## 📌 Project Overview
The **Student Grade Management System** is a CLI-based mini project developed in the **C programming language**.  
It allows users to record student details, calculate total marks across 5 subjects, compute overall percentages, assign letter grades (`A`, `B`, `C`, `D`, `F`), and view class summary statistics.

This project demonstrates core programming concepts in C, such as structures, modular functions, array manipulation, and input validation.

---

## 🎯 Features
- **Student Record Entry:** Input student name, roll number, and marks for 5 subjects (Mathematics, Physics, Chemistry, English, Computer Science).
- **Input Validation:** Ensures marks are strictly between `0` and `100`.
- **Grade Calculation:** Automatically assigns letter grades based on percentage:
  - `A` : 90% – 100%
  - `B` : 80% – 89.99%
  - `C` : 70% – 79.99%
  - `D` : 60% – 69.99%
  - `F` : Below 60%
- **Formatted Scorecard Output:** Displays clean tabular scorecards for individual students.
- **Class Summary Statistics:** Displays the total student count, class average percentage, and details of the top performer.

---

## 🛠️ C Concepts & Technologies Used
- **Language:** C (C99 standard compatible)
- **Concepts Applied:**
  - `struct` for grouping student attributes
  - Functions for modular code organization
  - `for` and `while` loops
  - Conditional statements (`if-else`, `switch-case`)
  - Input buffer handling (`scanf`, `fgets`)

---

## 🚀 How to Compile and Run

### 1. Using GCC (Terminal / Command Prompt)
Navigate to the project directory and run:

```bash
# Compile the C program
gcc -o student_grade_manager student_grade_manager.c

# Run the executable (Linux/macOS)
./student_grade_manager

# Run the executable (Windows)
student_grade_manager.exe
```

---

## 📋 Program Workflow
1. Launch the application to view the main menu options.
2. Select **`1`** to enter a new student's record and subject marks.
3. Select **`2`** to display scorecards for all registered students.
4. Select **`3`** to view class-wide statistics (highest percentage & class average).
5. Select **`4`** to exit the application.
