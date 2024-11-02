#include "util/util.h"
#include "util/logger.h"

void to_json(json& j, const SDL_Point& p) {
    j = json{{"x", p.x}, {"y", p.y}};
}
void from_json(const json& j, SDL_Point& p) {
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

void to_json(json& j, const SDL_Rect& r) {
    j = json{{"x", r.x}, {"y", r.y}, {"w", r.w}, {"h", r.h}};
}
void from_json(const json& j, SDL_Rect& r) {
    j.at("x").get_to(r.x);
    j.at("y").get_to(r.y);
    j.at("w").get_to(r.w);
    j.at("h").get_to(r.h);
}

void to_json(json& j, const SDL_Color& c) {
    j = json{{"r", c.r}, {"g", c.g}, {"b", c.b}, {"a", c.a}};
}
void from_json(const json& j, SDL_Color& c) {

    //RGB
    if(j.find("r") == j.end() || j.find("g") == j.end() || j.find("b") == j.end()) {
        log(LogLevel::ERROR, "Color missing required fields: {r, g, b}");
        return;
    }

    j.at("r").get_to(c.r);
    j.at("g").get_to(c.g);
    j.at("b").get_to(c.b);

    //Alpha
    if(j.find("a") == j.end()) {
        c.a = 255;
    } else {
        j.at("a").get_to(c.a);
    }

    
}
