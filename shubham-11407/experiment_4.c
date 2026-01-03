#include <stdio.h>

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    if (a > b)
        printf("%d is largest\n", a);
    else
        printf("%d is largest\n", b);

    return 0;
}