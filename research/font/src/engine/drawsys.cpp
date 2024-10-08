/*
PDAFontResearch - engine/drawsys.cpp

Drawing function defininitions
*/

#include "engine.h"
#include <SDL2/SDL.h>
#include <SDL_render.h>

// Set render system color
void set_color(int r, int g, int b) {
    set_color(r, g, b, 255);
}
void set_color(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void set_color(SDL_Color color) {
    set_color(color.r, color.g, color.b, color.a);
}

void draw_point(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}
void draw_point(SDL_Point pos) {
    draw_point(pos.x, pos.y);
}

void draw_line(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void draw_line(SDL_Point p1, SDL_Point p2) {
    draw_line(p1.x, p1.y, p2.x, p2.y);
}

void draw_polyline(SDL_Point* points, int len) {
    SDL_RenderDrawLines(renderer, points, len);
}

void draw_polygon(SDL_Point* points, int len) {
    SDL_RenderDrawLines(renderer, points, len);
    draw_line(points[len-1], points[0]);
}

void draw_rectangle(int x, int y, int w, int h) {
    draw_rectangle({x, y, w, h});
}
void draw_rectangle(SDL_Point pos, int w, int h) {
    draw_rectangle({pos.x, pos.y, w, h});
}
void draw_rectangle(SDL_Rect rect) {
    SDL_RenderDrawRect(renderer, &rect);
}

//TODO: fill functions

void fill_polygon(SDL_Point* points, int len) {

}

void fill_rectangle(int x, int y, int w, int h) {

}
void fill_rectangle(SDL_Point pos, int w, int h) {

}
void fill_rectangle(SDL_Rect rect) {

}
