/* Find the limits of the int type.*/

#include <stdio.h>

int main() {
	setbuf(stdout, NULL);
    int n = 0;
	while (n + 1 > n) {
		n = n + 1;
	}
	printf("The largest int is %d\n", n);
}
