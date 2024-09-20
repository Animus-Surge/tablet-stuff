#pragma once

/*
pda object.h

Object definitions
*/

#include "component/component.h"

#include <SDL2/SDL.h>

#include <functional>
#include <vector>

class Object {
protected:
    SDL_Point position;
    std::vector<BaseComponent*> components;
    const char* name;
public:
    Object(const char* name, std::function<void()> initfn);
    ~Object();

    void addComponent(BaseComponent* component) {
        components.push_back(component);
    }
    void removeComponent(int index) {
        components.erase(components.begin() + index);
    }

    void setPosition(int x, int y) {
        position.x = x;
        position.y = y;
    }
    void setPosition(SDL_Point position) {
        this->position = position;
    }
    SDL_Point getPosition() {
        return position;
    }

    void update();
    void render();
};
