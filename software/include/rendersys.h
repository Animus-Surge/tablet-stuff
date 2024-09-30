#pragma once

/*
pda rendersys.h

Render subsystem interface
*/

#include <SDL2/SDL.h>

extern SDL_Renderer* renderer;
extern SDL_Window* window;

void set_render_color(int r, int g, int b, int a);
void set_render_color(SDL_Color color);

// Basic drawing functions
void draw_point(int x, int y);
void draw_point(SDL_Point point);
void draw_point_thick(int x, int y, int thickness);
void draw_point_thick(SDL_Point point, int thickness);

void draw_line(int x1, int y1, int x2, int y2);
void draw_line(SDL_Point point1, SDL_Point point2);
void draw_line_thick(int x1, int y1, int x2, int y2, int thickness);
void draw_line_thick(SDL_Point point1, SDL_Point point2, int thickness);

void draw_polyline(SDL_Point* points, int num);
void draw_polyline_thick(SDL_Point* points, int num, int thickness);

void draw_rect(int x, int y, int w, int h);
void draw_rect(SDL_Rect rect);
void draw_rect_thick(int x, int y, int w, int h, int thickness);
void draw_rect_thick(SDL_Rect rect, int thickness);

void draw_polygon(SDL_Point* points, int num);
void draw_polygon_thick(SDL_Point* points, int num, int thickness);

//Ellipsoids
void draw_circle(int x, int y, int radius);
void draw_circle(SDL_Point point, int radius);
void draw_circle_thick(int x, int y, int radius, int thickness);
void draw_circle_thick(SDL_Point point, int radius, int thickness);

void draw_ellipse(int x, int y, int rx, int ry);
void draw_ellipse(SDL_Point point, int rx, int ry);
void draw_ellipse_thick(int x, int y, int rx, int ry, int thickness);
void draw_ellipse_thick(SDL_Point point, int rx, int ry, int thickness);

// Filled shapes
void fill_rect(int x, int y, int w, int h);
void fill_rect(SDL_Rect rect);

void fill_polygon(SDL_Point* points, int num);

void fill_circle(int x, int y, int radius);
void fill_circle(SDL_Point point, int radius);

void fill_ellipse(int x, int y, int rx, int ry);
void fill_ellipse(SDL_Point point, int rx, int ry);

// Rendering system

void init_render();
void shutdown();
