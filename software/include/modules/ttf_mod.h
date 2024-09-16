#pragma once

/*
pda modules/ttf_mod.h

Text rendering system
*/

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <map>
#include <string>

extern std::map<std::string, TTF_Font*> fonts;

void ttf_init();
void ttf_quit();

TTF_Font* ttf_load_font(const char* path, const char* nick, int size);
void ttf_unload_font(const char* nick);

void ttf_render_text(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect* dest);
void ttf_render_text(const std::string& text, const std::string& font, int size, SDL_Color color, SDL_Rect* dest);
