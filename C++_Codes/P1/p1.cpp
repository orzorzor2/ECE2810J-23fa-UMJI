#include "io.h"

int main() {
    double MonthlyPayment = GetParam("Please enter the monthly payment: ", 1, 100000);
    double InterestRate = GetParam("Please enter the interest rate: ", 0, 1); //interest rate of a year
    double duration = GetParam("Please enter the duration of the loan, in years: ", 1, 100); // Repayment years

    PrintHeader();

    double Balance = 0;
    double Interest;

    for (int i = 12 * duration; i > 0; i--) {
        Balance = 12 * (MonthlyPayment + Balance) / (12 + InterestRate); // Solution to an equation of the four parameters
        Interest = Balance * InterestRate / 12;
        PrintMonthlyData(i, MonthlyPayment - Interest, Interest, Balance);
    }
}
