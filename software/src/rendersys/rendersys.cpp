#include "rendersys.h"
#include "pda.h"

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

void init_render() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEBUG_SCREEN_WIDTH, DEBUG_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(1);
    }
}

void shutdown() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}
