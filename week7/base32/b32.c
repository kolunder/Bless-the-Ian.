#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// Struct to store capacity of string array and the string itself.
struct text {
	int size;
	char *array;
};
typedef struct text text;

// Binary Printing for visualisation.
void binary(int n, char s[9]) {
    s[8] = '\0';
    int i = 7;
    while (i != -1) {
        if ((n & 1) == 1) {
            s[i] = '1';
        } else {
            s[i] = '0';
        }
        n = n >> 1;
        i--;
    }
}

// Print a number in binary.
void printBinary(int n) {
    char s[33];
    binary(n, s);
    printf("%s", s);
}

// Create new string object.
void *new(char *s) {
	int n = strlen(s) + 1;
    text *t = malloc(sizeof(text) + n);
    t->array = malloc(n);

    strcpy(t->array, s);
    t->size = n;
    return t;
}

// Create new text object with the binary code as a String.
void newCode(text *t) {
	text *s = new("");
	char temp[9];

	s->array = realloc(s->array, 64);
	for (int i = 0; i < strlen(t->array); i++) {
		binary(t->array[i], temp);
		strcat(s->array, temp);
	}
	s->array[64] = '\0';
	s->size = strlen(s->array) + 1;

	printf("Binary String : %s\n", s->array);
	
}

// Buffer the input string.
void buffer(text *t) {
	int charAdd = 5 - ((t->size-1) % 5);

	t->array = realloc(t->array, sizeof(t->array) + charAdd);
	t->size = t->size + charAdd;

	char temp[charAdd];
	for (int i = 0; i < charAdd; i++ ) {
		temp[i] = charAdd + '0';
	}
	temp[charAdd] = '\0';
	strcat(t->array, temp);
	
}

// Bundle binary string into array of 5-character strings.

void bundle(text *t) {
}
// ---------------------------------------------------------------------------------------------
// Testing
void testBuffer() {
	text *t = new("John");
	buffer(t);
	assert(strlen(t->array) % 5 == 0);
	free(t);
}

void testnewCode() {
	text *t = new("John");

}

void test() {
	testBuffer();

}

//void addBuffer(text *t, int n) 

int main(int n, const char *args[n]) {
	test();
	
	if (n == 2) {
		char s[strlen(args[1]) + 1];
		strcpy(s, args[1]);

		text *t = new(s);
		buffer(t);
		newCode(t);
		free(t);
	}



	

}

