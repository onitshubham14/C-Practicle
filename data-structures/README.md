# 📚 Fundamental Data Structures in C

## 📌 Overview
This directory contains clean, well-commented C implementations of fundamental linear Data Structures: **Stack** and **Queue**. Each program features an interactive command-line interface for performing core operations, error handling for overflow/underflow conditions, and visual feedback.

---

## 🛠️ Implemented Data Structures

### 1. Stack (`stack.c`)
- **Principle:** LIFO (Last In, First Out)
- **Primary Operations:**
  - `push(item)`: Add an element to the top of the stack.
  - `pop()`: Remove and return the top element.
  - `peek()`: View the top element without removing it.
  - `isFull()` / `isEmpty()`: Check stack status bounds.
- **Time Complexity:**
  - Push: $\mathcal{O}(1)$
  - Pop: $\mathcal{O}(1)$
  - Peek: $\mathcal{O}(1)$

### 2. Queue (`queue.c`)
- **Principle:** FIFO (First In, First Out)
- **Primary Operations:**
  - `enqueue(item)`: Add an element to the rear of the queue.
  - `dequeue()`: Remove and return the front element.
  - `peek()`: View the front element.
  - `isFull()` / `isEmpty()`: Check queue status bounds.
- **Time Complexity:**
  - Enqueue: $\mathcal{O}(1)$
  - Dequeue: $\mathcal{O}(1)$
  - Peek: $\mathcal{O}(1)$

---

## 🚀 How to Compile and Run

### 1. Stack Implementation
```bash
# Navigate to the data-structures directory
cd data-structures

# Compile Stack
gcc -o stack stack.c

# Run Stack Program (Linux/macOS)
./stack

# Run Stack Program (Windows)
stack.exe
```

### 2. Queue Implementation
```bash
# Compile Queue
gcc -o queue queue.c

# Run Queue Program (Linux/macOS)
./queue

# Run Queue Program (Windows)
queue.exe
```
