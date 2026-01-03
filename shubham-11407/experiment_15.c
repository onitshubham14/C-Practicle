#include <stdio.h>

int main() {
    int a[5], key, found = 0;
    printf("Enter 5 elements:\n");
    for (int i = 0; i < 5; i++)
        scanf("%d", &a[i]);

    printf("Enter element to search: ");
    scanf("%d", &key);

    for (int i = 0; i < 5; i++) {
        if (a[i] == key) {
            found = 1;
            break;
        }
    }

    if (found)
        printf("Element found\n");
    else
        printf("Element not found\n");

    return 0;
}