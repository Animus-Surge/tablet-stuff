#include "rendersys.h"

SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

void init_render() {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    if(window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        exit(1);
    }
}
