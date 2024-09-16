#pragma once

/*
pda rendersys.h

Render subsystem interface
*/

#include <SDL2/SDL.h>

#define DEBUG_SCREEN_WIDTH 1024
#define DEBUG_SCREEN_HEIGHT 600

extern SDL_Color current_color;
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// Create and initialize render system, with window size and title
void init(int, int, const char*);

// Start the render subsystem
void run();

// Gracefully terminate the render subsystem
void shutdown();

// Helpers
void set_render_color(SDL_Color);

//Flat rendering
void render_line(int, int, int, int);
void render_line(SDL_Point, SDL_Point);
void render_point(int, int);
void render_point(SDL_Point);
void render_circle(int, int, int);
void render_circle(SDL_Point, int);
void render_rect(int, int, int, int);
void render_rect(SDL_Rect);
void render_polygon(SDL_Point[], int);

//Fill rendering
void fill_rect(int, int, int, int);
void fill_rect(SDL_Rect);
void fill_circle(int, int, int);
void fill_circle(SDL_Point, int);
void fill_polygon(SDL_Point[], int);

//Text rendering
void render_text(const char*, int, int);
void render_text(const char*, SDL_Point);
