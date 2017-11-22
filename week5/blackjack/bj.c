#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Constants for the cards.
enum card {T, J, Q, K, A};
typedef enum card card;

// Constants for validity checking.
enum validity {OK, BadLetter, BadDigit};
typedef enum validity validity;

// Constant for Bust.
enum {Bust};

// Structure for the game.
struct game { char hand[42]; int score; int aceCount;};
typedef struct game game;

//-------LOGIC----------


//------GAMEPLAY-------

void  count(char cmd) {
	int aceCount;
	for (int i = 0; i != strlen(cmd); i++) {
		if(strcmp("A", cmd[i])) aceCount++;
	}

	printf("Aces: %d\n", aceCount);
	//printf("Score: %d\n", g->score);
}

char * ask() {
	static char cmb[42];
	printf("Your Combination: ");
	fgets(cmb, 42, stdin);
	cmb[strlen(cmb)-1] = '\0';
	return cmd;
}


//------TESTING---------

// void testConvert() {
// 	assert(convert(T)==10);
// 	assert(convert(J)==10);
// 	assert(convert(Q)==10);
// 	assert(convert(K)==10);
// }

void test() {
	//testConvert();
	//printf("All test pass\n");

}

int main(int n, char *args[]) {

	game gamedata;
    game *g = &gamedata;

	if (n == 1) test();
	if (n == 2 && (strcmp(args[1], "P") == 0)) {
		count(ask());
	}


}

