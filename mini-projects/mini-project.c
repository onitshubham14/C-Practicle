#include <stdio.h>

int main() {
    float principal, rate, balance, interest;
    int years, i;
    int valid;

    /* Validate principal amount */
    do {
        char input[100];
        char extra;

        printf("Enter principal amount: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: Unable to read input.\n");
            valid = 0;
            continue;
        }

        if (sscanf(input, "%f %c", &principal, &extra) != 1) {
            printf("Error: Please enter a numeric value.\n");
            valid = 0;
        } else if (principal <= 0) {
            printf("Error: Principal amount must be greater than 0.\n");
            valid = 0;
        } else {
            valid = 1;
        }

    } while (!valid);

    /* Validate interest rate */
    do {
        char input[100];
        char extra;

        printf("Enter rate of interest (in %%): ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: Unable to read input.\n");
            valid = 0;
            continue;
        }

        if (sscanf(input, "%f %c", &rate, &extra) != 1) {
            printf("Error: Please enter a numeric value.\n");
            valid = 0;
        } else if (rate <= 0) {
            printf("Error: Interest rate must be greater than 0.\n");
            valid = 0;
        } else {
            valid = 1;
        }

    } while (!valid);

    /* Validate number of years */
    do {
        char input[100];
        char extra;

        printf("Enter number of years: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: Unable to read input.\n");
            valid = 0;
            continue;
        }

        if (sscanf(input, "%d %c", &years, &extra) != 1) {
            printf("Error: Please enter a whole number.\n");
            valid = 0;
        } else if (years <= 0) {
            printf("Error: Number of years must be greater than 0.\n");
            valid = 0;
        } else {
            valid = 1;
        }

    } while (!valid);

    /* Calculate compound interest */
    balance = principal;

    for (i = 1; i <= years; i++) {
        interest = balance * rate / 100;
        balance = balance + interest;
    }

    printf("Final balance after %d years = %.2f\n", years, balance);

    return 0;
}