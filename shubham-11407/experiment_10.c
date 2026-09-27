#include <stdio.h>

int main() {
    int a, b;
    char op;
    printf("Enter operator (+ - * /): ");
    scanf(" %c", &op);
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    switch (op) {
        case '+': printf("Result = %d\n", a + b); break;
        case '-': printf("Result = %d\n", a - b); break;
        case '*': printf("Result = %d\n", a * b); break;
        case '/':
            if (b == 0) {
                printf("Error: Division by zero is not allowed.\n");
            } else {
                printf("Result = %d\n", a / b);
            }
            break;
        default: printf("Invalid operator\n");
    }
    return 0;
}