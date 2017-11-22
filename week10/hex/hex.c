#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// Binary-hex conversion.
void hex(int n, char s[9]) {
	sprintf(s, "%02x", n);
}

// Writes binary file.
void write_file() {
	FILE *test = fopen("test.bin", "wb");
	for (int ch = 30 ; ch<=50; ch++) {
		fputc(ch,test);
	}
	fclose(test);

}

// Reads file and produces output.
int main(){
	write_file();

	FILE *read = fopen("test.bin", "rb");
	unsigned char b = fgetc(read);
	while (! feof(read)) {
		int flag = 0;
		while (flag!=15) {	
			char s[9];
			hex(b, s);
			if (strcmp(s, "ff")==0) break;
			printf("%s  ", s);
			flag++;
			b = fgetc(read);
		}
		printf("\n");
		flag = 0;

	}
	
	fclose(read);



}
