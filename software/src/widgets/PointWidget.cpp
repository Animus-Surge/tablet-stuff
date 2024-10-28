#include "objects/widget.h"
#include "engine/drawsys.h"

#include "util/util.h"

//Class function definitions

void PointWidget::init() {}

void PointWidget::event(SDL_Event* event) {}

void PointWidget::update() {}

void PointWidget::fixedUpdate(float dt) {}

void PointWidget::render(SDL_Renderer* renderer) {
    set_draw_color(this->color.r, this->color.g, this->color.b, this->color.a);
    point(renderer, this->m_point.x, this->m_point.y);
}

void PointWidget::clean() {}

//JSON serialization

void to_json(json& j, const PointWidget& p) {
    j = json{{"type", "point"}, {"color", p.get_color()}, {"point", p.get_point()}};
}

void from_json(const json& j, PointWidget& p) {
    j.at("color").get_to(p.color);
    j.at("point").get_to(p.m_point);
}
