#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <termios.h>

// Integer constants .
enum {Fail, Valid, Invalid};

// Check if input string has any repeats.
bool isRepeated(int n, char *arr) {
	
	int count = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < count - 1; i++) { 
    	for (int j = i + 1; j < count; j++) {
        	if (arr[i] == arr[j]) {
        		return true;
        	}

        }
    }
    return false;
}

// Check if input sring is valid.
bool isFormatted(int n, char *arr) {

	char strValue[12];
	sprintf(strValue, "%d", atoi(arr));

	if ((arr[0]=='0') || (n!=4)) {
		return false;
	} else if ((strcmp(strValue, arr) == 0)) {
        return true;
    } else {
        return false;
    }
}


// Check all validity.
int isValid(int n, char *arr) {
	if ((isFormatted(n,arr) == false) || (isRepeated(n, arr)==true)) {
		return Invalid;
	} else {
		return Valid;
	}
}

// Handles user input.
char * userInput() {

	static char guess[10];
	printf("Your Guess: ");
	fgets(guess, 10, stdin);
	guess[strlen(guess)-1] = '\0';

	return guess;
}

// Any characters that match in value and not position.
int nonExactMatch(const char *arr1, const char *arr2) {
	
	int count = sizeof(arr1) / sizeof(arr1[0]);
	int h1 = 0;

	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count; j++) {
			if ((arr1[i] == '\0') || (arr1[j] == '\0')) {
				break;
			} else if (arr2[i] == arr1[j]) {
				h1++;
			}
		}
	}
    return h1;
}

// Any characters that match both in value and in position.
int exactMatch (const char *arr1, const char *arr2) {

	int i;
	int h2 = 0;

	for (int i = 0; i <= 3; i++) {
		if (arr1[i] == arr2[i]) {
			h2 = h2 + 1;
		} 
	}

	return h2;

}

// Handles the gameplay.
int game(int n, const char code[]) {
	
	char *guess;
	int go = 0;

	while (go <= 5) {

		if (go == 5) {
			printf("Game over!\n");
			break;
		}
		printf("Guess number %d out of 5\n", go + 1);
		guess = userInput();

		int h1 = nonExactMatch(code, guess);
		int h2 = exactMatch(code, guess);

		if (h2 == 4) {
			printf("\vYou Win! Well Done!\v\n");
			break;
		} else  {
			printf("HINT: %d - %d\n", h1-h2, h2);
			go++;
		} 
	}

	return 0;
}

// User interface and testing.
//----------------------------------------------------------------------------------------------

//Printing.
void print(int type) {
    switch (type) {
        case Valid: printf("Game on!"); break;
        case Invalid: printf("Invalid Input"); break;
    }
    printf("\n");
}

//Tests
void testValidity() {
	assert(isValid(4, "1234") == Valid);
	assert(isValid(4, "5639") == Valid);
	assert(isValid(4, "4950") == Valid);
	assert(isValid(4, "2034") == Valid);
	assert(isValid(4, "6580") == Valid);

	assert(isValid(1, "1") == Invalid);
	assert(isValid(2, "12") == Invalid);
	assert(isValid(3, "298") == Invalid);
	assert(isValid(4, "0358") == Invalid);
	assert(isValid(4, "123k") == Invalid);
	assert(isValid(4, "abcd") == Invalid);
	assert(isValid(4, "ka98") == Invalid);
	assert(isValid(4, "0003") == Invalid);
	assert(isValid(4, "4444") == Invalid);
	assert(isValid(4, "0000") == Invalid);
	assert(isValid(4, "1252") == Invalid);
	assert(isValid(4, "4243") == Invalid);
	assert(isValid(4, "8238") == Invalid);
	assert(isValid(4, "0557") == Invalid);
}

void testNonExactMatch() {
	assert(nonExactMatch("1234", "4321") == 4);
	assert(nonExactMatch("6432", "3264") == 4);
	assert(nonExactMatch("2356", "6521") == 3);
	assert(nonExactMatch("1435", "3412") == 3);
	assert(nonExactMatch("5486", "6812") == 2);
	assert(nonExactMatch("1759", "2914") == 2);
	assert(nonExactMatch("1245", "1836") == 1);
	assert(nonExactMatch("9457", "2371") == 1);
	assert(nonExactMatch("5397", "4862") == 0);
	assert(nonExactMatch("1596", "3842") == 0);
}

void test() {
	testValidity();
	testNonExactMatch();
	printf("All test pass.\n");
}

// Handles input and output.
int main(int n, char *args[]) {

	if (n == 1) {
		test();
	} else if (n == 2) {
		print(isValid(strlen(args[1]), args[1]));
		if (isValid(strlen(args[1]), args[1])==Valid) {
			game(strlen(args[1]), args[1]);
		} else {
			puts("\vINVALID INPUT!");
			puts("To play, use:  ./bullscows m,  where m is an 4-digit secret value with no repetitions,");
        	puts("and the first digit IS NOT zero.\n");
		}

    } else {
    	puts("\v INVALID INPUT!");
        puts("To play, use:  ./bullscows m,  where m is an 4-digit secret value with no repetitions,");
        puts("and the first digit IS NOT zero.\n");
        return 1;
    }
}


/*puts("RULES:");
	puts("This is the game for 2 PLAYERS.\n\vFIRST PLAYER chooses a secret 4-DIGIT arr.\nSECOND PLAYER - makes attempts to guess the arr.\n");
	puts("They can offer ANY COMBINATIONS of 4 digits (WITHOUT REPETITIONS) - for each attempt the program answers with a HINT.\n");
	puts("THE HINT consists of TWO VALUES:\n\t");
	puts("- FIRST tells how many digits are GUESSED CORRECTLY AND ARE IN CORRECT POSITIONS");
	puts("- SECOND tells how many digits are GUESSED CORRECTLY BUT ARE IN WRONG POSITIONS.\n");
	puts("FOR EXAMPLE, if the SECRET VALUE is 1492 and SECOND`S GUESS is 2013 - THE HINT IS 0-2.");
	puts("And if the GUESS is 1865 - then the HINT would be 1-0.\n");*/
