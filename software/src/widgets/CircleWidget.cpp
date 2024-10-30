#include "engine/drawsys.h"
#include "objects/widget.h"

#include <SDL2/SDL.h>

//TODO: json

void CircleWidget::init() {}
void CircleWidget::event(SDL_Event* event) {}
void CircleWidget::update() {}
void CircleWidget::fixedUpdate(float dt) {}
void CircleWidget::render(SDL_Renderer* renderer) {
    if(this->fill) {
        //TODO
    } else {
        circle(renderer, this->position.x, this->position.y, this->radius, this->thickness);
    }
}
void CircleWidget::clean() {}
