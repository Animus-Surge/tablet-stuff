#pragma once

/*
pda util.h
Utility functions and structs
*/

#include <SDL2/SDL.h>

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define ARRLEN(x) sizeof(x) / sizeof(x[0])

//Conversion functions
void hex_to_rgb(std::string hex, SDL_Color* color);

//Validation functions
bool contains_key(const json& j, const std::string& key);
bool contains_keys(const json& j, const std::vector<std::string>& keys);


//JSON serialization for SDL datatypes
void to_json(json& j, const SDL_Point& p);
void from_json(const json& j, SDL_Point& p);

void to_json(json& j, const SDL_Rect& r);
void from_json(const json& j, SDL_Rect& r);

void to_json(json& j, const SDL_Color& c);
void from_json(const json& j, SDL_Color& c);

