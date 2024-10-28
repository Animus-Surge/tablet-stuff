#pragma once

/**
 * @file widget.h
 *
 * @brief Base widget definitions
 */

#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

//TODO: BaseWidget: Add position, size, rotation, and visibility properties

//Widget base class

class BaseWidget {
public:
    SDL_Color color = {255, 255, 255, 255}; // Color of the widget
    
    bool visible = true; // Visibility of the widget

    //Get if the widget is visible
    bool is_visible() const {
        return visible;
    }
    //Set the visibility of the widget
    void set_visible(bool visible) {
        this->visible = visible;
    }
    //Hide the widget
    void hide() {
        this->visible = false;
    }
    //Show the widget
    void show() {
        this->visible = true;
    }
    
    //Get the color of the widget
    SDL_Color get_color() const {
        return color;
    }
    //Set the color of the widget
    void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        this->color.r = r;
        this->color.g = g;
        this->color.b = b;
        this->color.a = a;
    }
    //Set the color of the widget
    void set_color(SDL_Color color) {
        this->color = color;
    }

    //Initialize the widget
    virtual void init() = 0;
    //Handle events
    virtual void event(SDL_Event* event) = 0;
    //Update the widget
    virtual void update() = 0;
    //Fixed update the widget
    virtual void fixedUpdate(float dt) = 0;
    //Render the widget
    virtual void render(SDL_Renderer* renderer) = 0;
    //Clean the widget
    virtual void clean() = 0;
};

//Point widget

class PointWidget : public BaseWidget {
public:
    SDL_Point m_point = {0, 0}; // Point to render
    SDL_Point get_point() const {
        return this->m_point;
    }
    void set_point(SDL_Point point) {
        this->m_point = point;
    }
    void set_point(int x, int y) {
        this->m_point.x = x;
        this->m_point.y = y;
    }

    void init() override;
    void event(SDL_Event* event) override;
    void update() override;
    void fixedUpdate(float dt) override;
    void render(SDL_Renderer* renderer) override;
    void clean() override;
};

void to_json(json& j, const PointWidget& p);
void from_json(const json& j, PointWidget& p);

//Line widget

class LineWidget : public BaseWidget {
public:
    SDL_Point start = {0, 0}; // Start point of the line
    SDL_Point end = {0, 0}; // End point of the line
    int thickness = 1; // Thickness of the line
    SDL_Point get_start() const {
        return start;
    }
    SDL_Point get_end() const {
        return end;
    }
    int get_thickness() const {
        return thickness;
    }
    void set_start(SDL_Point start) {
        this->start = start;
    }
    void set_end(SDL_Point end) {
        this->end = end;
    }
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
    void fixedUpdate(float dt) override;
    void render(SDL_Renderer* renderer) override;
    void clean() override;
};

void to_json(json& j, const LineWidget& l);
void from_json(const json& j, LineWidget& l);
