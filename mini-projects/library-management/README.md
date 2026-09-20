# 📚 Library Record Keeper – C Mini Project (File Handling)

## 📌 Project Overview
The **Library Record Keeper** is a C mini-project demonstrating persistent file storage using **C File I/O (`stdio.h`)**.  
It allows users to add book records, list all stored books, search books by unique Book ID or Author name, and calculate total stored books, preserving records in a binary database file (`library_books.dat`).

---

## 🎯 Key Features
- **Add Book Record:** Input Book ID, Title, Author, and Price. Appends to file using `"ab"` mode.
- **Display All Books:** Reads records sequentially from file using `fread()` and displays a tabular catalog.
- **Search by Book ID:** Quickly locates a record matching a specific ID.
- **Search by Author Name:** Performs substring searches across book author attributes.
- **Persistent Data:** Data persists even after the program exits.
- **Total Book Counter:** Calculates total registered records via `fseek()` and `ftell()`.

---

## 🛠️ C Concepts Demonstrated
- **File Modes:** `"ab"` (append binary), `"rb"` (read binary)
- **File Functions:** `fopen()`, `fclose()`, `fwrite()`, `fread()`, `fseek()`, `ftell()`
- **Structures:** `struct Book` encapsulating ID, Title, Author, and Price attributes
- **Strings:** `strstr()`, `strcspn()`, safe buffer reading with `fgets()`

---

## 🚀 How to Compile and Run

### 1. Using GCC (Terminal / Command Prompt)

```bash
# Navigate to project directory
cd mini-projects/library-management

# Compile the C program
gcc -o library_manager library_manager.c

# Run the executable (Linux/macOS)
./library_manager

# Run the executable (Windows)
library_manager.exe
```
