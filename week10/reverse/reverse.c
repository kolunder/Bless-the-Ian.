#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

void print(int n, const char *str) {
	for (int i = strlen(str); i --> 0;) {
		printf("%c", str[i]);
		}
	printf("\n");
}

int main(int n, char *args[n]) {
	char dot[] = ".";
	while (true) {
		char text[20];
		printf("> ");
		fgets(text, 20, stdin);
		text[strlen(text)-1] = '\0';

		if (strcmp(text,dot) == 0) break;
		print(strlen(text), text);

	} 
}


