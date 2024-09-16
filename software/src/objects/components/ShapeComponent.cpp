#include "component/component.h"
#include "rendersys.h"
#include <SDL_render.h>


ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point point, int thickness) {
    this->color = color;

    this->points.push_back(point);

    this->arg3 = thickness;

    this->type = 0;
}
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point p1, SDL_Point p2, int thickness) {
    this->color = color;

    this->points.push_back(p1);
    this->points.push_back(p2);

    this->arg3 = thickness;

    this->type = 1;
}
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point points[], int num_points, int thickness) {
    this->color = color;

    for (int i = 0; i < num_points; i++) {
        this->points.push_back(points[i]);
    }

    this->arg3 = thickness;

    this->type = 2;
}

ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point center, int radius, bool fill, int thickness) {}
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point center, int radiusX, int radiusY, bool fill, int thickness) {}

ShapeComponent::ShapeComponent(SDL_Color color, SDL_Rect rect, bool fill, int thickness) {
    this->color = color;
    this->arg3 = thickness;

    if (fill) {
        this->points.push_back({rect.x, rect.y});
        this->points.push_back({rect.x + rect.w, rect.y});
        this->points.push_back({rect.x + rect.w, rect.y + rect.h});
        this->points.push_back({rect.x, rect.y + rect.h});
        this->points.push_back({rect.x, rect.y});
    } else {
        this->points.push_back({rect.x, rect.y});
        this->points.push_back({rect.x + rect.w, rect.y});
        this->points.push_back({rect.x + rect.w, rect.y + rect.h});
        this->points.push_back({rect.x, rect.y + rect.h});
        this->points.push_back({rect.x, rect.y});
    }

    this->type = 5;
}
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point points[], int num_points, bool fill, int thickness) {}

ShapeComponent::~ShapeComponent() {

}

void ShapeComponent::render(SDL_Point posOffset) {
    set_render_color(this->color);

    switch(type) {
        case 0:
            SDL_RenderDrawPoint(renderer, points[0].x + posOffset.x, points[0].y + posOffset.y);
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawLine(renderer, points[0].x + posOffset.x, points[0].y + posOffset.y, points[1].x + posOffset.x, points[1].y + posOffset.y);
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderDrawLines(renderer, points.data(), points.size());
            break;
        case 5: //Rectangle
            SDL_Rect rect = {points[0].x + posOffset.x, points[0].y + posOffset.y, points[1].x - points[0].x, points[2].y - points[1].y};
            //Fill
            if (fill) {
                SDL_RenderFillRect(renderer, &rect);
            } else {
                SDL_RenderDrawRect(renderer, &rect);
            }
            break;
    }
}
