  /* Program that squares integers. */
#include <stdio.h>

//Function that defines the square of a number)
int square(int a) {
	int number = a * a;
	return number;
}

int main() {
    setbuf(stdout, NULL);
    int squaredNumber = square(50000);
    printf("The square of 42 is %d \n", squaredNumber);
    return 0;
}
