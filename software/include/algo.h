#pragma once

#include <SDL2/SDL.h>
#include <cmath>

int winding_number(SDL_Point* points, int num);
float cross_product(int x1, int y1, int x2, int y2);
