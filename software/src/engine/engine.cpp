#include "engine/engine.h"
#include "util/logger.h"

#include "objects/scene.h"

#include <SDL2/SDL_ttf.h>

void Engine::reload_scene() {
    if(this->current_scene_path == "pda::builtin") {
        log(LogLevel::ERROR, "Cannot reload builtin scene");
        return;
    }

    this->current_scene->clean();
    this->current_scene = load_scene(this->current_scene_path.c_str());
}

Engine::Engine(int width, int height, const char* title) {
    if(!init(width, height, title)) {
        log(LogLevel::ERROR, "Failed to initialize engine");
        clean();
        exit(EXIT_FAILURE);
    }
}

Engine::~Engine() {
    clean();
}

int Engine::init(int width, int height, const char* title) {
    log(LogLevel::INFO, "Initializing engine...");

    //Initialization
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        log(LogLevel::ERROR, "Failed to initialize SDL: %s", SDL_GetError());
        return 0;
    }

    //Initialize TTF
    if (TTF_Init() != 0) {
        log(LogLevel::ERROR, "Failed to initialize TTF: %s", TTF_GetError());
        return 0;
    }

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (this->window == nullptr) {
        log(LogLevel::ERROR, "Failed to initialize and create window: %s", SDL_GetError());
        return 0;
    }

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr) {
        log(LogLevel::ERROR, "Failed to initialize and create renderer: %s", SDL_GetError());
        return 0;
    }

    log(LogLevel::INFO, "Engine initialized successfully");
    
    //Set the current scene to an empty scene (TODO: splash screen?)
    this->current_scene = new Scene();

    this->running = true;

    return 1;
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
                } else if (event.key.keysym.sym == SDLK_F1) {
                    log(LogLevel::INFO, "Refreshing scene...");
                    this->current_scene->clean();

                    //Reload the current scene
                    this->set_scene("resources/test_scene.json");
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

void Engine::set_scene(const char* path) {
    this->current_scene = load_scene(path);
}
