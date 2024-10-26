#pragma once

/**
 * Rendering engine base class.
 */

#include <SDL2/SDL.h>

class Engine {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool running = true;

    void init(int width, int height, const char* title);
    void handleEvents();
    void update();
    void render();
    void clean();

public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void run();

    void shutdown();
};
