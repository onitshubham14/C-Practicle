#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Function declarations
void initQueue(Queue *q);
int isFull(Queue *q);
int isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int peek(Queue *q);
void display(Queue *q);

int main() {
    Queue q;
    initQueue(&q);
    int choice, value;

    printf("===================================================\n");
    printf("         ARRAY-BASED QUEUE IMPLEMENTATION          \n");
    printf("===================================================\n");

    while (1) {
        printf("\n--- QUEUE OPERATIONS MENU ---\n");
        printf("1. Enqueue (Insert Element)\n");
        printf("2. Dequeue (Remove Front Element)\n");
        printf("3. Peek (View Front Element)\n");
        printf("4. Display Queue Contents\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter integer value to enqueue: ");
                if (scanf("%d", &value) == 1) {
                    enqueue(&q, value);
                } else {
                    printf("Invalid integer input!\n");
                    while (getchar() != '\n');
                }
                break;

            case 2:
                value = dequeue(&q);
                if (value != -1) {
                    printf("Successfully dequeued element: %d\n", value);
                }
                break;

            case 3:
                value = peek(&q);
                if (value != -1) {
                    printf("Front element of queue: %d\n", value);
                }
                break;

            case 4:
                display(&q);
                break;

            case 5:
                printf("Exiting Queue program. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Choose between 1 and 5.\n");
        }
    }

    return 0;
}

// Initialize front and rear pointers
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is full
int isFull(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

// Enqueue element at rear
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("[Queue Overflow] Cannot enqueue %d. Queue is full!\n", value);
        return;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++(q->rear)] = value;
    printf("[Success] %d enqueued into queue.\n", value);
}

// Dequeue element from front
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("[Queue Underflow] Cannot dequeue. Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front++;

    // Reset pointers if queue becomes empty after dequeue
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }

    return value;
}

// Peek at front element of queue
int peek(Queue *q) {
    if (isEmpty(q)) {
        printf("[Queue Empty] No elements in queue to peek.\n");
        return -1;
    }
    return q->items[q->front];
}

// Display elements from front to rear
void display(Queue *q) {
    if (isEmpty(q)) {
        printf("[Queue Empty] Nothing to display.\n");
        return;
    }
    printf("\nQueue elements (Front to Rear):\n");
    printf("FRONT -> [ ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("] <- REAR\n");
}
