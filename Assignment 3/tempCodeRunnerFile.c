#include <stdio.h>

void calculateRepayment(float loan,float ir,int year,float amount) {
    if(loan<=0 || year <=0) {
        printf("\nYear %d: Remaining loan = 0.00\n",year);
        return;
    }
    loan-=amount;
    printf("\nYear %d: Remaining loan = %0.2f\n",year,loan);
    loan = loan* (1+ir/100.0);
    calculateRepayment(loan,ir,year-1,amount);

}

int main() {
    calculateRepayment(100000,5,3,35000);
}