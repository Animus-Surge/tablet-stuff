#pragma once

#include "pda.h"

#include <map>
#include <string>

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"

extern std::map<std::string, TTF_Font*> fontMap;

bool load_font(const char*, const char*, int);
void destroy_font(const char*);

void render_text(const char*, const char*, SDL_Point, SDL_Color);
