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

bool point_in_rect(SDL_Point point, SDL_Rect rect) {
    return (point.x >= rect.x && point.x <= rect.x + rect.w && point.y >= rect.y && point.y <= rect.y + rect.h);
}

bool point_in_polygon(SDL_Point point, SDL_Point *poly, int num) {
    int i, j;
    bool c = false;
    for (i = 0, j = num-1; i < num; j = i++) {
        if (((poly[i].y > point.y) != (poly[j].y > point.y)) &&
            (point.x < (poly[j].x - poly[i].x) * (point.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
            c = !c;
    }
    return c;
}
