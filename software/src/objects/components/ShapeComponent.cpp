#include "component/component.h"
#include "rendersys.h"
#include <SDL_render.h>
#include <cstdio>


ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point point, int thickness) {//Point
    this->color = color;

    this->points.push_back(point);

    this->arg3 = thickness;

    this->type = 0;
}
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point p1, SDL_Point p2, int thickness) {//Line
    this->color = color;

    this->points.push_back(p1);
    this->points.push_back(p2);

    this->arg3 = thickness;

    this->type = 1;
}
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point points[], int num_points, int thickness) {//Polyline
    this->color = color;

    for (int i = 0; i < num_points; i++) {
        this->points.push_back(points[i]);
    }

    this->arg3 = thickness;

    this->type = 2;
}

ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point center, int radius, bool fill, int thickness) {
    this->color = color;
    this->points.push_back(center);
    this->arg1 = radius;
    this->arg3 = thickness;
    this->fill = fill;
    this->type = 3;
}//Circle
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point center, int radiusX, int radiusY, bool fill, int thickness) {
    //TODO

    printf("W: Ellipse not implemented\n");
    this->type = 4; //Set type flag so render function ignores it
}//Ellipse

ShapeComponent::ShapeComponent(SDL_Color color, SDL_Rect rect, bool fill, int thickness) {//Rectangle
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
ShapeComponent::ShapeComponent(SDL_Color color, SDL_Point points[], int num_points, bool fill, int thickness) {
    this->color = color;
    this->arg3 = thickness;
    this->fill = fill;

    for (int i = 0; i < num_points; i++) {
        this->points.push_back(points[i]);
    }

    this->type = 6;
}//Polygon

ShapeComponent::~ShapeComponent() {

}

void ShapeComponent::render(SDL_Point posOffset) {
    set_render_color(this->color);

    switch(type) {
        case 0:
            render_point(points[0].x + posOffset.x, points[0].y + posOffset.y);
            break;
        case 1:
            render_line(points[0].x + posOffset.x, points[0].y + posOffset.y, points[1].x + posOffset.x, points[1].y + posOffset.y, arg3);
            break;
        case 2: //Polyline
            render_polyline(points.data(), points.size(), arg3);
            break;
        case 3: //Circle
            if(fill) {
                fill_circle(points[0], arg1);
            } else {
                render_circle(points[0], arg1, arg3);
            }
            break;
        case 4: //Ellipse (TODO)
            break;
        case 5: //Rectangle
        case 6: //Polygon
            if(fill) {
                fill_polygon(points.data(), points.size());
            } else {
                render_polygon(points.data(), points.size(), arg3);
            }
            break;

    }
}
