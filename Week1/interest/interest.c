/* Example program: Calculate Interest. */

#include <stdio.h>
double add(double a, double b) {
	double money = a + (a * (b / 100));
	return money;
}

int main() {
    setbuf(stdout, NULL);
    double cashflow = add(1000, 2.7);
    printf("Interest on 1000 pounds after a year at 2.7 percent interest is %f \n", cashflow);
    return 0;
}
