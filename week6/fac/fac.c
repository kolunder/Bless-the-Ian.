
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

//Enumerate validity constants
enum {Invalid, Prime, Valid};

struct count {int count;};
typedef struct count count;

// Check if number is prime.
bool isPrime(int i) {
    if (i <= 1) return false;
    for (int j = 2; j <= i/2; j++) {
  	  if (i % j == 0) return false;
  }      
    return true;
}


// Check validity by turning string into integer and comparing to original.
int isValid(const char *n) {
    char str[strlen(n)];
    long number = atol(n);
    sprintf(str, "%ld", number);

    if ((strcmp(n, str) == 0) && (number > 1)) return Valid;
    if (isPrime(number)) return Prime;
    else return Invalid;
}

// Conduct the factorisation and store factors in array.
int *factor(long number, count *c) {

	long i = 0;
	int count = 0;
	int j = 0;

	int capacity = sizeof(long);
	int *array = malloc(capacity);

	if (isPrime(number)) printf("%ld is already Prime\n", number);
	else {
		printf("%ld = ", number);

		for (i = 2; i < 10001; i++) {
			if (isPrime(i)) {
				while (number % i == 0) {

					while (j <= count) {
						array[j] = i;
						j++;
					}

					count++;
					number = number / i;
					

					capacity = capacity * 2;
					array = realloc(array, capacity);


					

				}
			}
		}
	}

	c->count = count;
	return array;
}


//------------------------------------------
// Printing input status messages.
void validity(const char *str) {
	if (isValid(str)==Invalid) {
		printf("\vUse ./fac n , where n is a positive integer.\n");
		printf("not exceeding 13 digits in length.\v");
	} else printf("\vloading...\v");
	printf("\n");
}
// Printing the array in desired format. 
void print(int *array, count *c) {
	int count = c->count;
	int i;
	for (i = 0; i < count-1; i++) {
		printf("%d * ", array[i]);
	}

	printf("%d\n", array[count-1]);
}

//------------------------------------------
// Testing

void testValidity() {
	assert(isValid("abc")       == Invalid);
	assert(isValid("a234b")     == Invalid);
	assert(isValid("0")         == Invalid);
	assert(isValid("1235642134")== Valid);
	assert(isValid("555555")    == Valid);
	assert(isValid("34539513")  == Valid);
}

void testPrime() {
	//assert(isPrime(1)==f);
	assert(isPrime(2)==true);
	assert(isPrime(3)==true);
	assert(isPrime(11)==true);
	assert(isPrime(13)==true);
	assert(isPrime(199)==true);
	assert(isPrime(200)==false);
	assert(isPrime(4)==false);
}

void test() {
	testValidity();
	testPrime();

}

//---I/O---

int main(int n, char *args[n]) {

	count countdata;
	count *c = &countdata; 

	if (n==1) test();
	if (n==2) {
		if (isValid(args[1])==Valid) {
			validity(args[1]);
			print(factor(atol(args[1]), c), c);
		} else validity(args[1]);
	}
}

