#include <stdio.h>

int main() {
    int a[5], temp;
    printf("Enter 5 elements:\n");
    for (int i = 0; i < 5; i++)
        scanf("%d", &a[i]);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4 - i; j++)
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }

    printf("Sorted array:\n");
    for (int i = 0; i < 5; i++)
        printf("%d ", a[i]);

    return 0;
}
