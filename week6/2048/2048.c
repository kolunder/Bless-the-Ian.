// Single persong 2048 game.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>

//----------------------------------------------
// Constants and declarations.

// Constants for Cell status.
enum Cell {O, X};
typedef enum Cell Cell;

// Constants for Moves.
enum Move {Up, Down, Left, Right};
typedef enum Move Move;

// Structure to hold the state of the game.
struct game {
	Cell grid[4][4];

};
typedef struct game game;

//----------------------------------------------
// Utility functions for readability.

// Swapping funcition.
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Convert values for pritning.
char show(int c) {
    if (c == O) return ' ';
    else return c - '0';
}

// twicee an integer.
int twice(game *g, int r, int c) {
	return g->grid[r][c] * 2;
}

// Check if a Cell is empty.
bool isEmpty(game *g, int r, int c) {
	if (g->grid[r][c] == O) return true;
	else return false;
}

// Check if above Cell is the same. --DOES NOT WORK, DO NOT USE--.
bool isDouble(game *g, int r, int c, Move a) {
	switch (a) {
		case Up :
			if (isEmpty(g, r-1, c)) return false; 
			if (g->grid[r][c] == g->grid[r-1][c]) return true; 
			break;
		case Down : if (g->grid[r][c] == g->grid[r+1][c]) return true; break;
		case Left : return false; break;
		case Right : return false; break;
	}
	return 0;

}

void zero(game *g, int r, int c) {
	g->grid[r][c] = 0;
}

//----------------------------------------------
// Functions providing logic to the game.

// Initialises the new game.
void newGame(game *g) {
    for ( int r = 0; r < 4; r++ ) {
        for ( int c = 0; c < 4; c++ ) {
            g->grid[r][c] = O;
        }
    }
}

// Add n random numbers to board. To be used each Move.
int addRandom(game *g, int n) {
	int count = 0;
	while (count < n) {

		g->grid[rand() % 4][rand() % 4] = (rand() % 2 + 1) * 2;
    	count++;
    }
    return count;

}

//--TODO-- Handles Movement.
void move(game *g, int r, int c, int dir) {


}

// Deals with the DOWN Move. 
void up(game *g) {
	for ( int r = 4; r --> 1;) {
        for ( int c = 4; c --> 0;) {
            if (isEmpty( g, r-1, c )) {
            	g->grid[r-1][c] = g->grid[r][c];
            	zero(g, r, c);
            }
            if (g->grid[r][c] == g->grid[r-1][c]) {
        		g->grid[r-1][c] = twice(g,r-1,c);
        		zero(g, r, c);
        	}	
        }
    }
}


// Deals with the DOWN Move. 
void down(game *g) {
    for ( int r = 0; r < 3; r++ ) {
        for ( int c = 0; c < 4; c++ ) {
        	if (isEmpty(g, r+1, c)) {
        		g->grid[r+1][c] = g->grid[r][c];
        		zero(g, r, c);
        	}
        	if (g->grid[r][c] == g->grid[r+1][c]) {
        		g->grid[r+1][c] = twice(g,r+1,c);;
        		zero(g, r, c);
        	}

    	}
	}
}

// Deals with the LEFT Move.
void left(game *g) {
	for ( int c = 4; c-->1; ) {
		for ( int r = 0; r < 4; r++ ) {
			if (isEmpty(g, r, c-1)) {
        		g->grid[r][c-1] = g->grid[r][c];
        		zero(g, r, c);
        	}

        	if (g->grid[r][c] == g->grid[r][c-1]) {
        		g->grid[r][c-1] = twice(g,r,c-1);;
        		zero(g, r, c);
        	}		     
        }
    }	
}

// Deals with the RIGHT Move.
void right(game *g) {
	for ( int c = 0; c < 3; c++ ) {
		for ( int r = 0; r < 4; r++ ) {
			if (isEmpty(g, r, c+1)) {
        		g->grid[r][c+1] = g->grid[r][c];
        		zero(g, r, c);
        	}
        	if (g->grid[r][c] == g->grid[r][c+1]) {
        		g->grid[r][c+1] = twice(g,r,c+1);;
        		zero(g, r, c);
        	}		  
        }
    }	
}


//----------------------------------------------
// Interface 

// Handles the display of the grid.
void display(game *g) {
	for (int r = 0; r < 4; r++) {
	    for (int c = 0; c < 4; c++) {
	    	printf("|");
	    	if (isEmpty(g,r,c)) printf("%c", ' ');
	    	else printf("%d", g->grid[r][c]);
	    	
	    }
	    printf("|\n");
	}
	printf("\n");
}


// Ask for user input.
void ask(game *g) {
	
	static char go[10];
	printf("Your go: ");
	fgets(go, 10, stdin);
	go[strlen(go)-1] = '\0';

	if (strcmp(go, "U")==0) up(g);
	if (strcmp(go, "D")==0) down(g);
	if (strcmp(go, "L")==0) left(g);
	if (strcmp(go, "R")==0) right(g);

	//addRandom(g, 1);
}


// Handles the gameplay
void play(game *g) {
	int n = 0;
	newGame(g);
	addRandom(g, 4);
	while (n < 100) {
		
		display(g);
		ask(g);
	}


}


//----------------------------------------------
// Testing.

// Test New Game.
void testNew(game *g) {
	*g = (struct game) {{{X, X, X, O},
						 {X, X, X, X},
				 		 {X, X, X, X},	
				 		 {X, X, X, X}}};
	newGame(g);
	assert(g->grid[0][0] == O);
    assert(g->grid[1][1] == O);
    assert(g->grid[2][2] == O);
    assert(g->grid[0][2] == O);
    assert(g->grid[2][1] == O);
}

// Test isEmpty function.
void testIsEmpty(game *g) {
	*g = (struct game) {{{O, O, X, O},
						 {O, X, O, O},
						 {O, O, X, O},
						 {O, O, O, O}}};

	assert(isEmpty(g, 0, 0) == true);
	assert(isEmpty(g, 0, 1) == true);
	assert(isEmpty(g, 2, 0) == true);
	assert(isEmpty(g, 0, 2) == false);
	assert(isEmpty(g, 1, 1) == false);
	assert(isEmpty(g, 2, 2) == false);
}

// Test addRandom function.
void testAddRandom(game *g) {
	assert(addRandom(g, 5)==5);
	assert(addRandom(g, 10)==10);
}

// Test twice function.
void testTwice(game *g) {
	*g = (struct game) {{{2, O, O, 4},
						 {O, O, O, O},
						 {O, O, O, 16},
						 {O, O, O, O}}};

	assert(twice(g, 0, 0)==4);
	assert(twice(g, 0, 3)==8);
	assert(twice(g, 2, 3)==32);
}

// Test zero function.
void testZero(game *g) {
	*g = (struct game) {{{2, O, O, 4},
						 {O, O, O, O},
						 {O, O, O, 16},
						 {O, O, O, O}}};
	zero(g,0,0);
	zero(g,2,2);
	assert(g->grid[0][0]==0);
	assert(g->grid[0][0]==0);
}

// Test isDouble function.
void testIsDouble(game *g) {
	*g = (struct game) {{{2, O, O, 4},   //0
						 {2, O, O, 4},   //1
						 {O, 8, O, 16},  //2
						 {O, O, O, O}}}; //3
	assert(isDouble(g, 1, 0, Up)==true);
	assert(isDouble(g, 2, 2, Up)==false); 
}

// Testing runs in the background.
void test() {
	game *g = malloc(sizeof(g));
	testNew(g);
	testIsEmpty(g);
	testAddRandom(g);
	testTwice(g);
	testIsDouble(g);
	testZero(g);
	
}

//----------------------------------------------
// Main Function
int main(int n, char *args[n]) {

	srand(time(NULL));

	game gamedata;
	game *g = &gamedata;

	if (n==1) {
		test();
		play(g);
	}
}

