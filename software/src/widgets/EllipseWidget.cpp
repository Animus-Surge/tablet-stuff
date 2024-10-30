#include "engine/drawsys.h"
#include "objects/widget.h"

#include <SDL2/SDL.h>

void EllipseWidget::init() {}
void EllipseWidget::event(SDL_Event* event) {}
void EllipseWidget::update() {}
void EllipseWidget::fixedUpdate(float dt) {}
void EllipseWidget::render(SDL_Renderer* renderer) {
    if(this->fill) {
        //TODO
    } else {
        ellipse(renderer, this->position.x, this->position.y, this->rx, this->ry, this->thickness);
    }
}
void EllipseWidget::clean() {}
