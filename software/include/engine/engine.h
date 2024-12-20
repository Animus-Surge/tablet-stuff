#pragma once

/**
 * Rendering engine base class.
 */

#include <SDL2/SDL.h>

#include "objects/scene.h"

class Engine {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool running = true;

    Scene* current_scene;
    std::string current_scene_path;

    //Initialize the engine, create the window and renderer
    int init(int width, int height, const char* title);

    //Event handling
    void handleEvents();

    //Update the current scene
    void update();

    //Update the current scene at a fixed rate, useful for physics
    void fixedUpdate(float dt);

    //Render the current scene
    void render();

    //Clean up the engine
    void clean();

public:
    Engine(int width, int height, const char* title);
    ~Engine();

    //Set the engine's current scene to a scene object
    void set_scene(Scene* scene) {
        this->current_scene = scene;
        this->current_scene_path = "pda::builtin";
    }

    //Set the engine's current scene to a scene file
    void set_scene(const char* path);
    void reload_scene(); //THIS WON'T WORK WITH pda::builtin

    //Run the engine
    void run();

    //Shutdown the engine
    void shutdown();
};
