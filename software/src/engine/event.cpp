#include "engine/event.h"

#include <SDL2/SDL.h>

/*
pda engine/event.cpp - Event system definitions
*/

bool key_state[SDL_NUM_SCANCODES] = {0};
bool mouse_state[4] = {0};

void poll_event() { //TODO: EITHER: define in main.cpp OR: define here
}

//Check if a point is within a polygon
bool point_in_polygon(SDL_Point point, SDL_Point* polygon, int poly_point_count) {
    //TODO
    return false;
}

//Check if a point is within a rectangle
bool point_in_rect(SDL_Point point, SDL_Rect rect) {
    return (point.x >= rect.x && point.x <= rect.w) &&
                (point.y >= rect.y && point.y <= rect.h);
}
