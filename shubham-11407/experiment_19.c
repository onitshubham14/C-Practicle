#include <stdio.h>
#include <string.h>

int main() {
    char s1[50] = "Hello";
    char s2[50] = "World";

    printf("Length of s1: %lu\n", strlen(s1));
    strcpy(s1, s2);
    strcat(s1, " C");
    printf("After copy & concat: %s\n", s1);

    if (strcmp(s1, s2) == 0)
        printf("Strings are equal\n");
    else
        printf("Strings are not equal\n");

    return 0;
}