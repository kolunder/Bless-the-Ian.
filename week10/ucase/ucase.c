#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// Convert string into upper-case.
char *up(const char *str) {
	char *newStr = malloc(sizeof(str));
	for (int i = 0; i < strlen(str); i++) {
		newStr[i] = (char) toupper(str[i]);
	}

	return newStr;
}

// Handle user input.
char *input() {
    char *line = malloc(100);
    fgets(line, 100, stdin);
    line[strlen(line)-1] = '\0';

    return line;

}

// Memory and printing.
int main() {
	const int max = 100;

    char *r = malloc(100);
    char *p = malloc(100);
    
    printf("Input file : ");
    r = input();
    printf("Output file : ");
    p = input();

    FILE *in = fopen(r, "r");
    FILE *out = fopen(p, "w");

    char line[max];
    fgets(line, max, in);
    while (! feof(in)) {
        strcpy(line, up(line));
        fprintf(out, "%s", line);
        fgets(line, max, in);
    }

    free(r);
    free(p);
    fclose(in);
    fclose(out);
}

