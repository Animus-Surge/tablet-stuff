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

    //Initialization
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
    
    //Set the current scene to an empty scene (TODO: splash screen?)
    this->current_scene = new Scene();

    this->running = true;
}

void Engine::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        //System events
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

        //Pass the event to the current scene, since it's not a system event
        this->current_scene->handleEvent(&event);
    }
}

void Engine::update() {
    this->current_scene->update();
}

void Engine::fixedUpdate(float dt) {
    this->current_scene->fixedUpdate(dt);
}

void Engine::render() {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->renderer);

    this->current_scene->render(this->renderer);

    SDL_RenderPresent(this->renderer);
}

void Engine::run() {
    log(LogLevel::INFO, "Starting!");
    
    //Create fixed update timer
    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time;
    float dt;

    while (this->running) {
        //General update
        handleEvents(); //Events
        update(); //Update
        render(); //Render

        //Fixed update
        current_time = SDL_GetTicks();
        dt = (current_time - last_time) / 1000.0f;
        fixedUpdate(dt);
    }
}

void Engine::shutdown() { //TODO: shutdown screen?
    log(LogLevel::INFO, "Stopping!");
    this->running = false;
}

void Engine::clean() {
    log(LogLevel::INFO, "Cleaning up engine...");
    this->current_scene->clean();

    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
