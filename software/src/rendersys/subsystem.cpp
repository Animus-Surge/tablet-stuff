#include "rendersys.h"

SDL_Color current_color = {0, 0, 0, 255};
SDL_Renderer* renderer = NULL;
SDL_Window* window = NULL;

void set_render_color(SDL_Color color) {
    current_color = color;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void init(int width, int height, const char *title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}

void run() {
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        set_render_color(SDL_Color{0, 0, 0, 0});
        SDL_RenderClear(renderer);
        set_render_color(SDL_Color{255, 0, 0, 255});

        fill_rect(10, 10, 100, 100);

        SDL_RenderPresent(renderer);
    }
}

void shutdown() {}
