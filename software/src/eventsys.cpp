#include "eventsys.h"
#include <SDL_scancode.h>

SDL_Point* current_mouse_pos = NULL;
SDL_Point* click_pos = NULL;

bool keystate[SDL_NUM_SCANCODES] = {false};
bool mousestate[5] = {false};

void set_mousestate(uint8_t button, bool du) {
    mousestate[button] = du;
}

bool is_mousedown(uint8_t button) {
    return mousestate[button];
}

void set_keystate(SDL_Scancode sc, bool du) {
    keystate[sc] = du;
}

bool is_keydown(SDL_Scancode sc) {
    return keystate[sc];
}
