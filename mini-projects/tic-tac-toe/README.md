# 🎮 2-Player Tic-Tac-Toe – C Mini Project

## 📌 Project Overview
An interactive, console-based **2-Player Tic-Tac-Toe Game** developed in the **C programming language**.  
It allows two players to play rounds of Tic-Tac-Toe taking turns as `Player 1 (X)` and `Player 2 (O)`, track cumulative match wins/draws across rounds, and enjoy clean board rendering in the terminal.

---

## 🎯 Game Features
- **Interactive 3x3 Grid:** Visual ASCII board displaying cell numbers `1` through `9`.
- **2-Player Turn Based Gameplay:** Alternate between Player 1 (`X`) and Player 2 (`O`).
- **Input Validation:** Prevents invalid inputs (outside `1-9`) and blocks selecting already-occupied positions.
- **Win & Draw Detection:** Evaluates all 3 rows, 3 columns, and 2 diagonals after every move.
- **Scoreboard Tracking:** Keeps track of Player 1 wins, Player 2 wins, and Draw counts across multiple rounds.
- **Replayability Option:** Prompts players to replay rounds without losing their score history.

---

## 🛠️ C Concepts Used
- **Language Standard:** C99 / C11
- **Data Structures:** 2D character arrays (`char board[3][3]`)
- **Functions & Scope:** Modular game loop decomposition (`playGame`, `checkWin`, `checkDraw`, `isValidMove`, `displayBoard`)
- **Control Flow:** `while`, `do-while` loops, conditional logic, input buffer clearing

---

## 🚀 How to Compile and Run

### 1. Using GCC (Terminal / Command Prompt)

```bash
# Navigate to the mini-project directory
cd mini-projects/tic-tac-toe

# Compile the C program
gcc -o tic_tac_toe tic_tac_toe.c

# Run the executable (Linux/macOS)
./tic_tac_toe

# Run the executable (Windows)
tic_tac_toe.exe
```

---

## 🕹️ How to Play
1. The game displays a numbered grid:
   ```text
        |     |     
     1  |  2  |  3  
   _____|_____|_____
        |     |     
     4  |  5  |  6  
   _____|_____|_____
        |     |     
     7  |  8  |  9  
        |     |     
   ```
2. Player 1 (`X`) chooses a position number from `1` to `9`.
3. Player 2 (`O`) chooses an available position on their turn.
4. The first player to align 3 of their marks horizontally, vertically, or diagonally wins!
5. If all 9 cells are filled without 3 aligned marks, the round ends in a **Draw**.
