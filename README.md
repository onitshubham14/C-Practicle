# 💻 C Language Practicals & Mini-Projects Repository

A curated open-source collection of **C programming practicals**, **lab experiments**, **data structures**, and **interactive CLI mini-projects**.

---

## 📁 Repository Structure

```text
C-Practicle/
├── data-structures/             # Linear & non-linear Data Structure implementations
│   ├── stack.c                  # LIFO Stack implementation
│   ├── queue.c                  # FIFO Queue implementation
│   └── README.md                # Data structures documentation & time complexities
├── mini-projects/               # Interactive CLI mini-projects in C
│   ├── student-grade-manager/   # Student Grade Management System
│   ├── tic-tac-toe/             # 2-Player Tic-Tac-Toe Console Game
│   ├── mini-project.c           # Banking Interest Calculation system
│   └── README.md                # Mini-projects overview
└── shubham-11407/               # University C Lab Experiments (1 to 19)
    └── experiment_1.c ... 19.c  # Basic C programs, loops, arrays, pointers, functions
```

---

## 🚀 Quick Navigation & Project Index

| Category | Program / Project Name | Description | Key C Concepts Used |
| :--- | :--- | :--- | :--- |
| **Mini Project** | [Student Grade Manager](file:///mini-projects/student-grade-manager/student_grade_manager.c) | Student scorecard & grade calculator with class statistics | `struct`, arrays, functions, input validation |
| **Mini Project** | [Tic-Tac-Toe Game](file:///mini-projects/tic-tac-toe/tic_tac_toe.c) | Interactive 2-Player console grid game with scoreboard | 2D Arrays, game loop, win condition matrix |
| **Mini Project** | [Banking Interest Calculator](file:///mini-projects/mini-project.c) | Yearly compound interest & balance updater | `for` loops, float arithmetic, CLI |
| **Data Structures** | [Array-based Stack](file:///data-structures/stack.c) | LIFO stack operations (`push`, `pop`, `peek`) | Arrays, pointers, boundary checks |
| **Data Structures** | [Array-based Queue](file:///data-structures/queue.c) | FIFO queue operations (`enqueue`, `dequeue`, `peek`) | Arrays, front/rear pointers, reset logic |
| **Lab Practicals** | [Lab Experiments 1-19](file:///shubham-11407/) | University lab practical submissions | Basic I/O, operators, logic, arrays |

---

## 🛠️ How to Compile & Run C Programs

Ensure you have a GCC compiler installed on your environment.

### 1. Windows (MinGW / Command Prompt / PowerShell)
```powershell
# Compile any C program (e.g., Stack)
gcc -Wall -Wextra -o program.exe path/to/file.c

# Run the executable
.\program.exe
```

### 2. Linux / macOS (GCC / Clang)
```bash
# Compile any C program
gcc -Wall -Wextra -o program path/to/file.c

# Run the executable
./program
```

---

## 🤝 Contribution Guidelines

We welcome open-source contributions! Follow these steps to contribute new C practicals, algorithms, or mini-projects:

1. **Fork the Repository** to your GitHub account.
2. **Find or Create an Issue**: Describe the feature/project you wish to add. Make sure to append `assign me` at the end of the issue description.
3. **Create a Feature Branch**:
   ```bash
   git checkout -b feature/YourAmazingFeature
   ```
4. **Commit Your Changes**:
   ```bash
   git commit -m 'feat(category): add description of feature'
   ```
5. **Push to the Branch**:
   ```bash
   git push origin feature/YourAmazingFeature
   ```
6. **Open a Pull Request (PR)**: Reference your assigned issue (`Closes #issue_number`) and await review!
