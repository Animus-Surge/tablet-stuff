#pragma once

#include <SDL2/SDL.h>

/*
pda event.h - Event system management
 */

//TODO: size this according to SDL's max buttons
extern bool key_state[SDL_NUM_SCANCODES];
extern bool mouse_state[4]; 

void poll_event();

bool point_in_polygon(SDL_Point point, SDL_Point* polygon, int poly_point_count);
bool point_in_rect(SDL_Point point, SDL_Rect rect);

static void update_keystate(bool state, int kc) {
    key_state[kc] = state;
}

static void update_mousestate(bool state, int btn) {
    mouse_state[btn] = state;
}

static bool is_keydown(int kc) {
    return key_state[kc];
}

static bool is_mousedown(int btn) {
    return mouse_state[btn];
}