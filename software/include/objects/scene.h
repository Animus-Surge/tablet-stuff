#pragma once

/**
 * Base scene class.
 */

#include "objects/widget.h"

#include <SDL2/SDL.h>

#include <map>
#include <string>

//TODO: implement file loading for scenes

void load_scene(const char* path);

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

    virtual void init() = 0;
    void handleEvent(SDL_Event* event);
    void update();
    void render(SDL_Renderer* renderer);
    void clean();
};

class BasicTestScene : public Scene {
public:
    void init() override;
};

