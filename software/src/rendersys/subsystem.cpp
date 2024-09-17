#include "component/component.h"
#include "object.h"
#include "rendersys.h"

#include "scene_manager.h"
#include <SDL_rect.h>
#include <SDL_scancode.h>

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

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
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
            if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }

        //Clear
        set_render_color(SDL_Color{0, 0, 0, 0});
        SDL_RenderClear(renderer);

        //Draw - TODO: scenes
        set_render_color(SDL_Color{255, 0, 0, 255});

        SDL_Rect rect = {
            20, 20, 100, 100
        };

        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);

        //Clamp to 60 FPS
        SDL_Delay(1000 / 60);
    }
}

void shutdown() {
    //Deinit everything
}
