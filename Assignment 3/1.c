#include <stdio.h>
// Assumed there is an amount variable as well,
// since it is not specified in the question itself.

void calculateRepayment(float loan, float ir, int year, float amount)
{
    if (loan <= 0 || year <= 0)
    {
        printf("\nYear %d: Remaining loan = 0.00\n", year + 1);
        return;
    }
    loan = loan * (1 + ir / 100.0); // Apply interest first
    loan -= amount;
    printf("Enter Extra yearly paymentes or zero if none:  ");
    float f;
    scanf("%f", &f);
    loan -= f;
    loan = 0;
    printf("\nYear %d: Remaining loan = %.2f\n", (year - (year - 1)), loan);
    calculateRepayment(loan, ir, year - 1, amount);
}

// Recursion is good as for this problem because it lets the
// computer handle each year one by one, keeping track of the
// loan as it changes, and makes it easy to add things like
// extra payments for each year.

int main()
{
    calculateRepayment(100000, 5, 3, 35000);
}