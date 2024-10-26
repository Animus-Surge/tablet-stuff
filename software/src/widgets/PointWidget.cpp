#include "objects/widget.h"

void PointWidget::init() {}

void PointWidget::event(SDL_Event* event) {}

void PointWidget::update() {}

void PointWidget::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderDrawPoint(renderer, this->point.x, this->point.y);
}

void PointWidget::clean() {}
