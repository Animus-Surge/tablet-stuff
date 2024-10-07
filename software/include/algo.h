#pragma once

#include "pda.h"

#include <SDL2/SDL.h>
#include <cmath>

int winding_number(SDL_Point* points, int num);
float cross_product(int x1, int y1, int x2, int y2);

int min(int a, int b);
int max(int a, int b);
