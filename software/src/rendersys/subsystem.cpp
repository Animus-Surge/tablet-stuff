#include "component/component.h"
#include "eventsys.h"
#include "object.h"
#include "rendersys.h"


#include "scene_manager.h"
#include <SDL_events.h>
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
    //Temp scene
    Scene* scene = new Scene();
    Object* obj = new Object("Test", []() {});
    obj->addComponent(new ShapeComponent(SDL_Color{255, 0, 0, 255}, SDL_Point{10, 10}, 1));
    obj->addComponent(new ShapeComponent({0, 255, 0, 255}, {20, 10}, {110, 100}, 4));
    obj->addComponent(new ShapeComponent({0, 0, 255, 255}, {120, 10, 90, 90}, false, 4));
    obj->addComponent(new ShapeComponent({255, 0, 255, 255}, {512, 300}, 200, false, 1));
    scene->add_object(obj);
    current_scene = scene;

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }

            //TODO: character typing event

            // System event handling

            //Keyboard
            if (e.type == SDL_KEYDOWN) {
                set_keystate(e.key.keysym.scancode, true);
            } else if (e.type == SDL_KEYUP) {
                set_keystate(e.key.keysym.scancode, false);
            }
            //Mouse
            else if (e.type == SDL_MOUSEBUTTONDOWN) {

            } else if (e.type == SDL_MOUSEBUTTONUP) {

            } else if (e.type == SDL_MOUSEMOTION) {
                SDL_Point mouse_pos = {e.motion.x, e.motion.y};
                set_mouse_pos(&mouse_pos);
            }

        }

        //Clear
        set_render_color(SDL_Color{0, 0, 0, 0});
        SDL_RenderClear(renderer);


            //Draw common rendering components
            current_scene->render();
            // current_scene->update();


        SDL_RenderPresent(renderer);

        //Clamp to 60 FPS
        SDL_Delay(1000 / 60);
    }
}

void shutdown() {
    //Deinit everything
    delete current_scene;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
