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

class PointWidget : public BaseWidget {
private:
    SDL_Point point = {0, 0}; // Point to render
public:
    void set_point(int x, int y) {
        this->point.x = x;
        this->point.y = y;
    }

    void init() override;
    void event(SDL_Event* event) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void clean() override;
};

class LineWidget : public BaseWidget {
private:
    SDL_Point start = {0, 0}; // Start point of the line
    SDL_Point end = {0, 0}; // End point of the line
    int thickness = 1; // Thickness of the line
public:
    void set_start(int x, int y) {
        this->start.x = x;
        this->start.y = y;
    }
    void set_end(int x, int y) {
        this->end.x = x;
        this->end.y = y;
    }
    void set_thickness(int thickness) {
        this->thickness = thickness;
    }

    void init() override;
    void event(SDL_Event* event) override;
    void update() override;
    void render(SDL_Renderer* renderer) override;
    void clean() override;
};
