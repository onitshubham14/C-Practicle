#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "library_books.dat"

typedef struct {
    int bookId;
    char title[100];
    char author[50];
    float price;
} Book;

// Function declarations
void addBook();
void displayAllBooks();
void searchBookById();
void searchBookByAuthor();
void displayBookCount();

static int isValidBook(const Book *book) {
    return memchr(book->title, '\0', sizeof(book->title)) != NULL &&
           memchr(book->author, '\0', sizeof(book->author)) != NULL;
}

int main() {
    int choice;

    printf("===================================================\n");
    printf("     LIBRARY RECORD KEEPER (C FILE HANDLING)       \n");
    printf("===================================================\n");

    while (1) {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Add New Book Record\n");
        printf("2. Display All Book Records\n");
        printf("3. Search Book by ID\n");
        printf("4. Search Book by Author\n");
        printf("5. View Total Book Count\n");
        printf("6. Exit\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayAllBooks();
                break;
            case 3:
                searchBookById();
                break;
            case 4:
                searchBookByAuthor();
                break;
            case 5:
                displayBookCount();
                break;
            case 6:
                printf("\nExiting Library System. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice! Choose an option between 1 and 6.\n");
        }
    }

    return 0;
}

// Appends a new book record to binary file
void addBook() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("[Error] Unable to open or create database file!\n");
        return;
    }

    Book b;
    printf("\n--- Add New Book Details ---\n");
    printf("Enter Book ID: ");
    scanf("%d", &b.bookId);
    getchar(); // Clear newline

    printf("Enter Book Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Author Name: ");
    fgets(b.author, sizeof(b.author), stdin);
    b.author[strcspn(b.author, "\n")] = '\0';

    printf("Enter Price ($): ");
    scanf("%f", &b.price);

    fwrite(&b, sizeof(Book), 1, fp);
    fclose(fp);

    printf("🎉 Book record saved successfully to file!\n");
}

// Reads and displays all book records from binary file
void displayAllBooks() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n[Notice] No book records database found yet. Add some books first!\n");
        return;
    }

    Book b;
    int count = 0;

    printf("\n===================================================================\n");
    printf("                       LIBRARY BOOK CATALOG                        \n");
    printf("===================================================================\n");
    printf(" %-8s | %-30s | %-20s | %-8s\n", "ID", "Title", "Author", "Price ($)");
    printf("-------------------------------------------------------------------\n");

    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (!isValidBook(&b)) {
            printf("[Error] Corrupt book record encountered. Skipping record.\n");
            continue;
        }

        printf(" %-8d | %-30s | %-20s | %8.2f\n", b.bookId, b.title, b.author, b.price);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf(" No books registered in database.\n");
    }
    printf("===================================================================\n");
}

// Searches for a book by unique Book ID
void searchBookById() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n[Notice] Database file does not exist.\n");
        return;
    }

    int searchId, found = 0;
    Book b;

    printf("\nEnter Book ID to search: ");
    scanf("%d", &searchId);

    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (!isValidBook(&b)) {
            printf("[Error] Corrupt book record encountered. Skipping record.\n");
            continue;
        }

        if (b.bookId == searchId) {
            printf("\n--- Book Found ---\n");
            printf(" ID     : %d\n", b.bookId);
            printf(" Title  : %s\n", b.title);
            printf(" Author : %s\n", b.author);
            printf(" Price  : $%.2f\n", b.price);
            printf("-------------------\n");
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("❌ Book with ID %d not found in database.\n", searchId);
    }
}

// Searches for books matching an author name
void searchBookByAuthor() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n[Notice] Database file does not exist.\n");
        return;
    }

    char searchAuthor[50];
    int found = 0;
    Book b;

    getchar(); // Clear buffer
    printf("\nEnter Author Name to search: ");
    fgets(searchAuthor, sizeof(searchAuthor), stdin);
    searchAuthor[strcspn(searchAuthor, "\n")] = '\0';

    printf("\n--- Search Results for Author: \"%s\" ---\n", searchAuthor);
    while (fread(&b, sizeof(Book), 1, fp) == 1) {
        if (!isValidBook(&b)) {
            printf("[Error] Corrupt book record encountered. Skipping record.\n");
            continue;
        }

        if (strstr(b.author, searchAuthor) != NULL) {
            printf(" ID: %d | Title: %s | Price: $%.2f\n", b.bookId, b.title, b.price);
            found++;
        }
    }

    fclose(fp);

    if (found == 0) {
        printf("❌ No books found matching author \"%s\".\n", searchAuthor);
    } else {
        printf("Found %d matching record(s).\n", found);
    }
}

// Counts total books registered in binary file
void displayBookCount() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\nTotal Books Registered: 0\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    long totalBytes = ftell(fp);
    int totalBooks = totalBytes / sizeof(Book);
    fclose(fp);

    printf("\n📊 Total Books Registered in Database: %d\n", totalBooks);
}
