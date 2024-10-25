#pragma once

/**
 * @file widget.h
 *
 * @brief Base widget definitions
 */

#include <SDL2/SDL.h>

class BaseWidget {
protected:
    SDL_Point position = {0, 0}; // Position of the widget
    float rotation = 0.0; // Rotation of the widget
    SDL_FPoint scale = {1, 1}; // Scale of the widget
    SDL_Color color = {255, 255, 255, 255}; // Color of the widget
public:
    
    void set_position(int x, int y) {
        this->position.x = x;
        this->position.y = y;
    }
    void set_rotation(float rotation) {
        this->rotation = rotation;
    }
    void set_scale(float x, float y) {
        this->scale.x = x;
        this->scale.y = y;
    }
    void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
    }

    virtual void init() = 0;
    virtual void event(SDL_Event* event) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void clean() = 0;
};
