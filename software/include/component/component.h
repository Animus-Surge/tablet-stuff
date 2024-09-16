#pragma once

/*
pda component/component.h

Base component definitions
*/

#include <SDL2/SDL.h>

#include <vector>


// Base component
class BaseComponent {
protected:
    bool active = true;
public:
    BaseComponent();
    ~BaseComponent();

    void update();
    void render(SDL_Point posOffset = {0, 0});

    void setActive(bool active) {
        this->active = active;
    }
    void activate() {
        setActive(true);
    }
    void deactivate() {
        setActive(false);
    }
    bool isActive() {
        return active;
    }
};


// Interfaces
class Colorfield {
public:
    SDL_Color color;
};


// Components

class ShapeComponent : public BaseComponent, public Colorfield {
private:
    int arg1; //RadiusX, num_points
    int arg2; //RadiusY
    int arg3; //thickness

    std::vector<SDL_Point> points;

    bool fill = false;

    int type; //0: point, 1: line, 2: segments, 3: circle, 4: ellipse, 5: rectangle, 6: polygon
public:
    //Create a point
    ShapeComponent(SDL_Color color, SDL_Point point, int thickness = 1);
    //Create a line
    ShapeComponent(SDL_Color color, SDL_Point p1, SDL_Point p2, int thickness = 1);
    //Create a polyline
    ShapeComponent(SDL_Color color, SDL_Point points[], int num_points, int thickness = 1);
    //Create a circle
    ShapeComponent(SDL_Color color, SDL_Point center, int radius, bool fill = false, int thickness = 1);
    //Create an ellipse
    ShapeComponent(SDL_Color color, SDL_Point center, int radiusX, int radiusY, bool fill = false, int thickness = 1);
    //Create a rectangle
    ShapeComponent(SDL_Color color, SDL_Rect rect, bool fill = false, int thickness = 1);
    //Create a polygon
    ShapeComponent(SDL_Color color, SDL_Point points[], int num_points, bool fill = false, int thickness = 1);

    ~ShapeComponent();

    void update() {}
    void render(SDL_Point posOffset = {0, 0});
};

//Event/interaction components

// Widgets
// - Button
// - Textbox
// - Checkbox
// - Radio button

//Text components defined in modules/ttf_mod.h

//Sprites and images - TODO: module
