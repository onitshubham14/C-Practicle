#include <stdio.h>

int main() {
    float principal, rate, balance, interest;
    int years, i;

    printf("=========================================\n");
    printf("     BANKING INTEREST SIMULATOR v2.0     \n");
    printf("=========================================\n");

    
    printf(" Enter principal amount ($): ");
    if (scanf("%f", &principal) != 1 || principal < 0) {
        printf("[Error] Please enter a valid positive amount.\n");
        return 1;
    }

    printf(" Enter rate of interest (%%): ");
    if (scanf("%f", &rate) != 1 || rate < 0) {
        printf("[Error] Please enter a valid positive interest rate.\n");
        return 1;
    }

    printf(" Enter number of years: ");
    if (scanf("%d", &years) != 1 || years < 0) {
        printf("[Error] Please enter a valid number of years.\n");
        return 1;
    }

    balance = principal;

    printf("\n-----------------------------------------\n");
    printf("         COMPUTING COMPOUND INTEREST     \n");
    printf("-----------------------------------------\n");

    
    for (i = 1; i <= years; i++) {
        interest = balance * rate / 100; 
        balance = balance + interest;     
        printf(" Year %2d -> Interest Earned: $%-9.2f | Balance: $%.2f\n", i, interest, balance);
    }

    printf("=========================================\n");
    printf(" SUMMARY REPORT\n");
    printf("=========================================\n");
    printf(" Initial Principal : $%.2f\n", principal);
    printf(" Interest Rate     : %.2f%%\n", rate);
    printf(" Duration          : %d years\n", years);
    printf(" ----------------------------------------\n");
    printf(" Final Balance     : $%.2f\n", balance);
    printf(" Total Profit Made : $%.2f\n", balance - principal);
    printf("=========================================\n");

    return 0;
}