#include "rendersys.h"

//Colors

void set_render_color(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void set_render_color(SDL_Color color) {
    set_render_color(color.r, color.g, color.b, color.a);
}

//Basic drawing

void draw_point(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}
void draw_point(SDL_Point point) {
    draw_point(point.x, point.y);
}

void draw_line(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void draw_line(SDL_Point p1, SDL_Point p2) {
    draw_line(p1.x, p1.y, p2.x, p2.y);
}

void draw_rect(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}
void draw_rect(SDL_Rect rect) {
    draw_rect(rect.x, rect.y, rect.w, rect.h);
}

void draw_polyline(SDL_Point* points, int num) {
    if (num < 2) return;
    if (num == 2) {
        draw_line(points[0], points[1]);
        return;
    }

    for (int i = 0; i < num - 1; i++) {
        draw_line(points[i], points[i + 1]);
    }
}

void draw_polygon(SDL_Point* points, int num) {
    draw_polyline(points, num);
    draw_line(points[num - 1], points[0]);
}

//Ellipsoids

void draw_ellipse(int x, int y, int rx, int ry) {
    //Midpoint ellipse algorithm
    int dx = 0;
    int dy = ry;
    int rx2 = rx * rx;
    int ry2 = ry * ry;

    int p = ry2 - rx2 * ry + 0.25 * rx2;
    int px = 0;
    int py = 2 * rx2 * dy;

    while (px < py) {
        draw_point(x + dx, y + dy);
        draw_point(x - dx, y + dy);
        draw_point(x + dx, y - dy);
        draw_point(x - dx, y - dy);

        if (p < 0) {
            dx++;
            px += 2 * ry2;
            p += ry2 + px;
        }
        else {
            dx++;
            dy--;
            px += 2 * ry2;
            py -= 2 * rx2;
            p += ry2 + px - py;
        }
    }
}
void draw_ellipse(SDL_Point center, int rx, int ry) {
    draw_ellipse(center.x, center.y, rx, ry);
}

void draw_circle(int x, int y, int r) {
    draw_ellipse(x, y, r, r);
}
void draw_circle(SDL_Point center, int r) {
    draw_ellipse(center, r, r);
}

//Filled shapes
void fill_polygon(SDL_Point *, int) {

}
void fill_rect(int x, int y, int w, int h) {

}
void fill_rect(SDL_Rect rect) {

}
