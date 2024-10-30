#include "util/util.h"

void hex_to_rgb(const char* hex_str, SDL_Color* color) {
    //Check if the string is valid
    if(hex_str[0] != '#' || strlen(hex_str) != 7) {
        return;
    }

    //Convert the hex string to an integer
    unsigned int hex = 0;
    sscanf(hex_str, "#%x", &hex);

    //Extract the RGB values
    color->r = (hex >> 16) & 0xFF;
    color->g = (hex >> 8) & 0xFF;
    color->b = hex & 0xFF;
    color->a = 0xFF;
}
