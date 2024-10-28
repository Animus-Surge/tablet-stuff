#pragma once

/**
 * Base scene class.
 */

#include "objects/widget.h"

#include <SDL2/SDL.h>

#include <map>
#include <string>

class Scene {
protected:
    std::map<std::string, BaseWidget*> widgets;

public:
    void add_widget(const std::string& name, BaseWidget* widget) {
        widgets[name] = widget;
    }

    BaseWidget* get_widget(const std::string& name) {
        return widgets[name];
    }

    //Event handling
    void handleEvent(SDL_Event* event);

    //Update the scene
    void update();

    //Update the scene at a fixed rate
    void fixedUpdate(float dt);

    //Render the scene
    void render(SDL_Renderer* renderer);

    //Clean up the scene
    void clean();
};

//Load a scene from a file
Scene* load_scene(const char* path);

