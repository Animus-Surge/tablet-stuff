#include "eventsys.h"
#include <SDL_scancode.h>

SDL_Point* current_mouse_pos = NULL;
SDL_Point* click_pos = NULL;

bool keystate[SDL_NUM_SCANCODES] = {false};

void set_keystate(SDL_Scancode sc, bool du) {
    keystate[sc] = du;
}
