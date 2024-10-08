#pragma once

/*
PDAFontResearch - engine.h

GUI engine, SDL wrapper
*/

#include <SDL2/SDL.h>

// Engine variables
extern SDL_Renderer* renderer;
extern SDL_Window* window;

// Rendering functions
void set_color(int r, int g, int b);
void set_color(int r, int g, int b, int a);
void set_color(SDL_Color color);

void draw_point(int x, int y);
void draw_point(SDL_Point pos);

void draw_line(int x1, int y1, int x2, int y2);
void draw_line(SDL_Point p1, SDL_Point p2);

void draw_polyline(SDL_Point* points, int len);

void draw_polygon(SDL_Point* points, int len);

void draw_rectangle(int x, int y, int w, int h);
void draw_rectangle(SDL_Point pos, int w, int h);
void draw_rectangle(SDL_Rect rect);

void fill_polygon(SDL_Point* points, int len);

void fill_rectangle(int x, int y, int w, int h);
void fill_rectangle(SDL_Point pos, int w, int h);
void fill_rectangle(SDL_Rect rect);

// Engine functions

void init();

void loop();

void destroy();
