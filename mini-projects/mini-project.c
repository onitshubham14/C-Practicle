#include <stdio.h>
#include <math.h>

int main() {
    float principal, rate, balance, interest;
    float monthly_rate, emi;
    int years, months, i;

    /* Validate principal amount */
    printf("Enter principal amount: ");
    if (scanf("%f", &principal) != 1 || principal <= 0) {
        printf("Error: Principal amount must be greater than 0.\n");
        return 1;
    }

    /* Validate interest rate */
    printf("Enter rate of interest (in %%): ");
    if (scanf("%f", &rate) != 1 || rate <= 0) {
        printf("Error: Interest rate must be greater than 0.\n");
        return 1;
    }

    /* Validate loan tenure */
    printf("Enter number of years: ");
    if (scanf("%d", &years) != 1 || years <= 0) {
        printf("Error: Loan tenure must be greater than 0.\n");
        return 1;
    }

    /* Calculate compound interest */
    balance = principal;

    for (i = 1; i <= years; i++) {
        interest = balance * rate / 100;
        balance = balance + interest;
    }

    printf("Final balance after %d years = %.2f\n", years, balance);

    /* Calculate EMI */
    months = years * 12;
    monthly_rate = rate / (12 * 100);

    emi = (principal * monthly_rate * pow(1 + monthly_rate, months)) /
          (pow(1 + monthly_rate, months) - 1);

    printf("Monthly EMI for %d years = %.2f\n", years, emi);

    return 0;
}
