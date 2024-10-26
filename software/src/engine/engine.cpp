#include "engine/engine.h"
#include "util/logger.h"

Engine::Engine(int width, int height, const char* title) {
    init(width, height, title);
}

Engine::~Engine() {
    clean();
}

void Engine::init(int width, int height, const char* title) {
    log(LogLevel::INFO, "Initializing engine...");

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

    log(LogLevel::INFO, "Engine initialized successfully");

    this->running = true;

    //TEMPORARY
    
    

    //END TEMPORARY
}

void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    this->running = false;
                }
                break;
        }
    }
}

void Engine::update() {
    //Logic goes here...
}

void Engine::render() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    //Rendering goes here...

    SDL_RenderPresent(this->renderer);
}

void Engine::run() {
    log(LogLevel::INFO, "Starting!");

    while (this->running) {
        handleEvents();
        update();
        render();
    }
}

void Engine::shutdown() {
    log(LogLevel::INFO, "Stopping!");
    this->running = false;
}

void Engine::clean() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
