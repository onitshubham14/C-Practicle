#include <stdio.h>

int main() {
    double principal, rate, balance, interest;
    int years, i;

    printf("Enter principal amount: ");
    scanf("%lf", &principal);

    printf("Enter rate of interest (in %%): ");
    scanf("%lf", &rate);

    printf("Enter number of years: ");
    scanf("%d", &years);

    balance = principal;

    printf("\nYear\tInterest\tBalance\n");

    for (i = 1; i <= years; i++) {
        interest = balance * rate / 100;
        balance = balance + interest;

        printf("%d\t%.2f\t\t%.2f\n", i, interest, balance);
    }

    printf("\nFinal balance after %d years = %.2f\n", years, balance);

    return 0;
}