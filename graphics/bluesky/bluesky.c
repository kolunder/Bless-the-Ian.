/* Display blue sky for 10 seconds. */

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initialising SDL : %s\n", SDL_GetError());
        return 1;
    }

    printf("Intitialisation successful!\n");

    SDL_Quit();
}