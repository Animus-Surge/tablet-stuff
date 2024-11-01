#include "util/util.h"

void hex_to_rgb(const char* hex_str, SDL_Color* color) {
    //Check if the string is valid
    if(hex_str[0] != '#') {
        return;
    }

    //Check format
    if(strlen(hex_str) == 7) { //#RRGGBB
        sscanf(hex_str, "#%02x%02x%02x", &color->r, &color->g, &color->b);
        color->a = 255;
    } else if(strlen(hex_str) == 9) { //#RRGGBBAA
        sscanf(hex_str, "#%02x%02x%02x%02x", &color->r, &color->g, &color->b, &color->a);
    }
}
