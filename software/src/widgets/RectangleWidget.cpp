#include "engine/drawsys.h"
#include "objects/widget.h"

#include <SDL2/SDL.h>

//TODO: json

void RectangleWidget::init() {}
void RectangleWidget::event(SDL_Event* event) {}
void RectangleWidget::update() {}
void RectangleWidget::fixedUpdate(float dt) {}
void RectangleWidget::render(SDL_Renderer* renderer) {
    if(this->fill) {
        //TODO
    } else {
        rect(renderer, this->p_rect.x, this->p_rect.y, this->p_rect.w, this->p_rect.h, this->thickness);
    }
}
void RectangleWidget::clean() {}
