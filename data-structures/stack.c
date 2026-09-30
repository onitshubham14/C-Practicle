#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Function declarations
void initStack(Stack *s);
int isFull(Stack *s);
int isEmpty(Stack *s);
void push(Stack *s, int value);
int pop(Stack *s);
int peek(Stack *s);
void display(Stack *s);

int main() {
    Stack s;
    initStack(&s);
    int choice, value;

    printf("===================================================\n");
    printf("         ARRAY-BASED STACK IMPLEMENTATION          \n");
    printf("===================================================\n");

    while (1) {
        printf("\n--- STACK OPERATIONS MENU ---\n");
        printf("1. Push (Insert Element)\n");
        printf("2. Pop (Remove Top Element)\n");
        printf("3. Peek (View Top Element)\n");
        printf("4. Display Stack Contents\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to push: ");
                if (scanf("%d", &value) == 1) {
                    push(&s, value);
                } else {
                    printf("Invalid integer input!\n");
                    while (getchar() != '\n');
                }
                break;

            case 2:
                value = pop(&s);
                if (value != -1) {
                    printf("Successfully popped element: %d\n", value);
                }
                break;

            case 3:
                value = peek(&s);
                if (value != -1) {
                    printf("Top element of stack: %d\n", value);
                }
                break;

            case 4:
                display(&s);
                break;

            case 5:
                printf("Exiting Stack program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Choose between 1 and 5.\n");
        }
    }

    return 0;
}

// Initialize top index to -1
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push an element onto the stack
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("[Stack Overflow] Cannot push %d. Stack is full!\n", value);
        return;
    }
    s->items[++(s->top)] = value;
    printf("[Success] %d pushed onto stack.\n", value);
}

// Pop the top element from the stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("[Stack Underflow] Cannot pop. Stack is empty!\n");
        return -1;
    }
    return s->items[(s->top)--];
}

// Peek at the top element of the stack
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("[Stack Empty] No elements in stack to peek.\n");
        return -1;
    }
    return s->items[s->top];
}

// Display all stack elements from top to bottom
void display(Stack *s) {
    if (isEmpty(s)) {
        printf("[Stack Empty] Nothing to display.\n");
        return;
    }
    printf("\nStack elements (Top to Bottom):\n");
    printf("┌─────────┐\n");
    for (int i = s->top; i >= 0; i--) {
        printf("│  %5d  │ %s\n", s->items[i], (i == s->top) ? "<- TOP" : "");
    }
    printf("└─────────┘\n");
}
