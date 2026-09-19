#include <stdio.h>

int main() {
    int choice;
    float principal, rate, simple_interest, compound_interest, final_amount;
    int years, i;
    float balance;

    printf("Interest Calculation System\n");
    printf("----------------------------\n");
    printf("1. Simple Interest\n");
    printf("2. Compound Interest\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Error: Invalid choice.\n");
        return 1;
    }

    if (choice == 3) {
        printf("Exiting program.\n");
        return 0;
    }

    if (choice != 1 && choice != 2) {
        printf("Error: Please select a valid option.\n");
        return 1;
    }

    printf("Enter principal amount: ");
    if (scanf("%f", &principal) != 1 || principal <= 0) {
        printf("Error: Principal amount must be greater than 0.\n");
        return 1;
    }

    printf("Enter rate of interest (in %%): ");
    if (scanf("%f", &rate) != 1 || rate <= 0) {
        printf("Error: Interest rate must be greater than 0.\n");
        return 1;
    }

    printf("Enter number of years: ");
    if (scanf("%d", &years) != 1 || years <= 0) {
        printf("Error: Number of years must be greater than 0.\n");
        return 1;
    }

    if (choice == 1) {
        simple_interest = (principal * rate * years) / 100;
        final_amount = principal + simple_interest;

        printf("\nSimple Interest = %.2f\n", simple_interest);
        printf("Final Amount = %.2f\n", final_amount);
    }
    else {
        balance = principal;

        for (i = 1; i <= years; i++) {
            balance = balance + (balance * rate / 100);
        }

        compound_interest = balance - principal;
        final_amount = balance;

        printf("\nCompound Interest = %.2f\n", compound_interest);
        printf("Final Amount = %.2f\n", final_amount);
    }

    return 0;
}
