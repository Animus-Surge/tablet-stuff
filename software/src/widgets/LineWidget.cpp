#include "objects/widget.h"
#include "engine/drawsys.h"

#include "util/util.h"

//Class function definitions

void LineWidget::init() {}

void LineWidget::event(SDL_Event* event) {}

void LineWidget::update() {}

void LineWidget::fixedUpdate(float dt) {}

void LineWidget::render(SDL_Renderer* renderer) {
    //TODO: position, rotation, scale calculations
    set_draw_color(this->color.r, this->color.g, this->color.b, this->color.a);
    line(renderer, this->start.x, this->start.y, this->end.x, this->end.y, this->thickness);
}

void LineWidget::clean() {}

//JSON serialization

void to_json(json& j, const LineWidget& p) {
    j = json{{"type", "line"}, {"color", p.get_color()}, {"start", p.get_start()}, {"end", p.get_end()}, {"thickness", p.get_thickness()}};
}

void from_json(const json& j, LineWidget& p) {
    j.at("color").get_to(p.color);
    j.at("start").get_to(p.start);
    j.at("end").get_to(p.end);
    j.at("thickness").get_to(p.thickness);
}
