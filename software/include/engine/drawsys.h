#pragma once

/**
 * @file engine/drawsys.h
 *
 * @brief Drawing system definitions
 */

#include <SDL2/SDL.h>

extern SDL_Color draw_color;

inline void set_draw_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    draw_color.r = r;
    draw_color.g = g;
    draw_color.b = b;
    draw_color.a = a;
}

//Basic drawing functions
void point(SDL_Renderer* renderer, int x, int y);
void line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness);
void pline(SDL_Renderer* renderer, SDL_Point* points, int count, int thickness);
void rect(SDL_Renderer* renderer, int x, int y, int w, int h, int thickness);
void polygon(SDL_Renderer* renderer, SDL_Point* points, int count, int thickness);
void circle(SDL_Renderer* renderer, int x, int y, int r, int thickness);
void ellipse(SDL_Renderer* renderer, int x, int y, int rx, int ry, int thickness);

//Curves
void bezier(SDL_Renderer* renderer, SDL_Point start, SDL_Point control1, SDL_Point control2, SDL_Point end, float step);


//Filled drawing functions
void fill_rect(SDL_Renderer* renderer, int x, int y, int w, int h);
void fill_polygon(SDL_Renderer* renderer, SDL_Point* points, int count);
void fill_circle(SDL_Renderer* renderer, int x, int y, int r);
void fill_ellipse(SDL_Renderer* renderer, int x, int y, int rx, int ry);

//TODO: 3D?

