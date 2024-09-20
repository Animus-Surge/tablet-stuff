#pragma once

/*
pda eventsys.h

Event management system
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>

extern SDL_Point* current_mouse_pos;
extern SDL_Point* click_pos;

extern bool keystate[SDL_NUM_SCANCODES];

// Internal functions for state setting
inline void set_mouse_pos(SDL_Point* pos) {
    current_mouse_pos = pos;
}
inline void set_click_pos(SDL_Point* pos) {
    click_pos = pos;
}

void set_keystate(SDL_Scancode, bool);


//
