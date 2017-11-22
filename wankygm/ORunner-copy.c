
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

//struct------------------------------------------------------------------------

//structure to save each line of the graphics and score, highscore and
//placement of character
struct game{
  char l1[5];
  char l2[5];
  char l3[5];
  char l4[5];
  char l5[5];

  int placement;
  int score;
  int highscore;
};
typedef struct game game;

//code--------------------------------------------------------------------------

//prints out each array in a way that resembles a games graphics.
//shows user current score, high score, controls and how to quit game
void board(game *g){
  clear();

  printw("Welcome to 'O Runner'\n'o' and 'p' to move\n\n");
  printw("HIGH SCORE: %d\n", g->highscore);
  printw("|%c|%c|%c|%c|\n", g->l1[0], g->l1[1], g->l1[2], g->l1[3]);
  printw("|%c|%c|%c|%c|\n", g->l2[0], g->l2[1], g->l2[2], g->l2[3]);
  printw("|%c|%c|%c|%c|\n", g->l3[0], g->l3[1], g->l3[2], g->l3[3]);
  printw("|%c|%c|%c|%c|\n", g->l4[0], g->l4[1], g->l4[2], g->l4[3]);
  printw("|%c|%c|%c|%c|\n", g->l5[0], g->l5[1], g->l5[2], g->l5[3]);
  printw("Score: %d\n\n", g->score);
  printw("Press 'q' to quit\n");
}

//resets all variables and strings to initial values for start of new game
void start(game *g, char *d1){
  strcpy(g->l1, d1);
  strcpy(g->l2, d1);
  strcpy(g->l3, d1);
  strcpy(g->l4, d1);
  strcpy(g->l5, d1);
  g->l5[1] = 'I';
  g->score = 0;
}

//generates a random set of obstacles at top of screen for player to avoid
void generator(game *g, char *d2, char *d3, char *d4, char *d5){
  srand(time(NULL));
  int x = rand()%4;

  switch (x) {  //gives array of obsticles based on random number gen
    case 0:
    strcpy(g->l1, d2);
    break;
    case 1:
    strcpy(g->l1, d3);
    break;
    case 2:
    strcpy(g->l1, d4);
    break;
    case 3:
    strcpy(g->l1, d5);
    break;
  }
}

//allocates placement value based on current position of character
//this is pointless in current code but doesnt hurt and reduces ambiguity
void controlallo(game *g){
  if(g->l5[0] == 'I'){
    g->placement = 0;
  }else if(g->l5[1] == 'I'){
    g->placement = 1;
  }else if(g->l5[2] == 'I'){
    g->placement = 2;
  }else if(g->l5[3] == 'I'){
    g->placement = 3;
  }
}

//moves character based on user input to avoid obstacles
void control(game *g, int m){
  if(m == 'o'){
    if(g->placement != 0){
      g->placement--;
    }else{
      g->placement = 3;
    }
  }
  if(m == 'p'){
    if(g->placement != 3){
      g->placement++;
    }else{
      g->placement = 0;
    }
  }

  if(g->l5[0] == 'I'){
    g->l5[0] = ' ';
    g->l5[g->placement] = 'I';
  }else if(g->l5[1] == 'I'){
    g->l5[1] = ' ';
    g->l5[g->placement] = 'I';
  }else if(g->l5[2] == 'I'){
    g->l5[2] = ' ';
    g->l5[g->placement] = 'I';
  }else if(g->l5[3] == 'I'){
    g->l5[3] = ' ';
    g->l5[g->placement] = 'I';
  }
}

//uses a an extra array to check whether check whether character
//has collided with obstacle
bool collide(game *g, char *check, char *d2, char *d3, char *d4, char *d5){
  if(strcmp(check, d2) == 0){
    if(g->l5[0] == 'I'){
      return false;
    }else{
      return true;
    }
  }else if(strcmp(check, d3) == 0){
    if(g->l5[1] == 'I'){
      return false;
    }else{
      return true;
    }
  }else if(strcmp(check, d4) == 0){
    if(g->l5[2] == 'I'){
      return false;
    }else{
      return true;
    }
  }else if(strcmp(check, d5) == 0){
    if(g->l5[3] == 'I'){
      return false;
    }else{
      return true;
    }
  }
  return false;
}

//actions to take if character has collided - resets score and graphics
//keeps highscore saved
void gameover(game *g, char *d1){
  clear();

  printw("GAME OVER\n\n");
  printw("Score: %d\n\n", g->score);
  printw("Press 'q' to quit\n");
  if(g->score > g->highscore){
    g->highscore = g->score;
  }
  start(g, d1);
}

// moves obsticles down for game to run and implements collide Functions and
//gameover function
void mymove(game *g, char *d1, char *d2, char *d3, char *d4, char *d5){
  controlallo(g);
  char check[5];

  if(strcmp(g->l1, d1) == 0){
    generator(g, d2, d3, d4, d5);
    strcpy(g->l3, g->l2);
    strcpy(g->l2, d1);
    strcpy(g->l5, g->l4);
    strcpy(g->l4, d1);
    strcpy(check, g->l5);
    g->l5[g->placement] = 'I';
  }else if(strcmp(g->l2, d1) == 0){
    strcpy(g->l2, g->l1);
    strcpy(g->l1, d1);
    strcpy(g->l4, g->l3);
    strcpy(g->l3, d1);
    strcpy(g->l5, d1);
    g->l5[g->placement] = 'I';
    g->score++;
  }
  if(collide(g, check, d2, d3, d4, d5)){
    gameover(g, d1);
  }else{
    board(g);
  }
  sleep(1);
}

//function with logic to run the game
void play(game *g, char *d1, char *d2, char *d3, char *d4, char *d5){
  initscr();      //initialises screen to ncurses graphics
  cbreak();       //says to constantly scan for raw input
  noecho();       //says to not print what user inputs
  halfdelay(1);   //timing for how often to scan for input

  g->highscore = 0;

  start(g, d1);
  int m;
  do{
    m = getch();
    control(g, m);
    mymove(g, d1, d2, d3, d4, d5);
  }while(m != 'q');
  printw("Goodbye\n");
  endwin();     //ends graphics and game
}
//Testing-----------------------------------------------------------------------

//tests start 
void testnew(game *g, char *d1){
  start(g, d1);
  for(int i = 0; i <=4; i++){
    assert(g->l1[i] == d1[i]);
  }
  for(int i = 0; i <=4; i++){
    assert(g->l2[i] == d1[i]);
  }
  for(int i = 0; i <=4; i++){
    assert(g->l3[i] == d1[i]);
  }
  for(int i = 0; i <=4; i++){
    assert(g->l4[i] == d1[i]);
  }
}

//tests collide function
void testcollide(game *g, char *d2, char *d3, char *d4, char *d5){
  g->l5[1] = 'I';
  char check1[5] = " 000\0";
  assert(collide(g, check1, d2, d3, d4, d5) == true);
  char check2[5] = "0 00\0";
  assert(collide(g, check2, d2, d3, d4, d5) == false);
  char check3[5] = "00 0\0";
  assert(collide(g, check3, d2, d3, d4, d5) == true);
  char check4[5] = "000 \0";
  assert(collide(g, check4, d2, d3, d4, d5) == true);
}

//tests control function
void testcontrol(game *g){
  int m = 'o';
  g->placement = 1;
  control(g, m);
  assert(g->placement == 0);

  g->placement = 0;
  control(g, m);
  assert(g->placement == 3);

  m = 'p';
  g->placement = 1;
  control(g, m);
  assert(g->placement == 2);

  g->placement = 3;
  control(g, m);
  assert(g->placement == 0);
}

//all tests
void tests(game *g, char *d1, char *d2, char *d3, char *d4, char *d5){
  testnew(g, d1);
  testcollide(g, d2, d3, d4, d5);
  testcontrol(g);
  printf("all tests passed.\n");
}

//main--------------------------------------------------------------------------

int main(int n, char *arg[n]){
  game *g = malloc(sizeof(game));
  char d1[5] = "    \0";
  char d2[5] = " 000\0";
  char d3[5] = "0 00\0";
  char d4[5] = "00 0\0";
  char d5[5] = "000 \0";

  if(n == 1){
    play(g, d1, d2, d3, d4, d5);
  }else if(n == 2 && strcmp(arg[1], "t") == 0){
    tests(g, d1, d2, d3, d4, d5);
  }
  return 0;
}
