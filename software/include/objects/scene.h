#pragma once

/**
 * Base scene class.
 */

#include "objects/widget.h"
#include "objects/animation.h"

#include <SDL2/SDL.h>

#include <map>
#include <string>
#include <vector>

class Scene {
protected:
    std::map<std::string, BaseWidget*> widgets;
    std::string name;

    std::vector<AnimationTrack*> animations;

public:
    void set_name(const std::string& name) {
        this->name = name;
    }
    std::string get_name() const {
        return name;
    }

    void add_widget(const std::string& name, BaseWidget* widget) {
        widgets[name] = widget;
    }
    BaseWidget* get_widget(const std::string& name) {
        return widgets[name];
    }
    void remove_widget(const std::string& name) {
        widgets.erase(name);
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

