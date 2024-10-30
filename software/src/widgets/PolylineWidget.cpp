#include "engine/drawsys.h"
#include "objects/widget.h"

#include <SDL2/SDL.h>

void PolylineWidget::set_points(SDL_Point* points, int num) {
    for(int i = 0; i < num; i++) {
        this->points.push_back(points[i]);
    }
}
void PolylineWidget::add_point(SDL_Point point) {
    this->points.push_back(point);
}
void PolylineWidget::add_point_at(SDL_Point point, int pos) {
    this->points[pos] = point;
}

void PolylineWidget::init() {}
void PolylineWidget::event(SDL_Event* event) {}
void PolylineWidget::update() {}
void PolylineWidget::fixedUpdate(float dt) {}
void PolylineWidget::render(SDL_Renderer* renderer) {
    if(this->connect) {
        polygon(renderer, this->points.data(), this->points.size(), this->thickness);
    } else {
        pline(renderer, this->points.data(), this->points.size(), this->thickness);
    }

    //TODO: fill
}
void PolylineWidget::clean() {} //TODO
