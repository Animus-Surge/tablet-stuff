#include "engine/engine.h"
#include "util/logger.h"

Engine::Engine(int width, int height, const char* title) {
    init(width, height, title);
}

Engine::~Engine() {
    clean();
}

void Engine::init(int width, int height, const char* title) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log(LogLevel::ERROR, "Failed to initialize SDL: %s", SDL_GetError());
        return;
    }

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (this->window == nullptr) {
        log(LogLevel::ERROR, "Failed to initialize and create window: %s", SDL_GetError());
        return;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        log(LogLevel::ERROR, "Failed to initialize and create renderer: %s", SDL_GetError());
        return;
    }

    this->running = true;
}

void Engine::clean() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
