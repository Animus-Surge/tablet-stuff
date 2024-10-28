#pragma once

/*
pda util.h
Utility functions and structs
*/

#include <SDL2/SDL.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define ARRLEN(x) sizeof(x) / sizeof(x[0])


//JSON serialization for SDL datatypes

void to_json(json& j, const SDL_Point& p);
void from_json(const json& j, SDL_Point& p);

void to_json(json& j, const SDL_Rect& r);
void from_json(const json& j, SDL_Rect& r);

void to_json(json& j, const SDL_Color& c);
void from_json(const json& j, SDL_Color& c);

