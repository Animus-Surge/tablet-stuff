#include "util/util.h"
#include "util/logger.h"

#include <string>

#include <SDL2/SDL.h>

void hex_to_rgb(std::string hex_str, SDL_Color* color) {
    //Possible formats: #RRGGBB, #RRGGBBAA
    if(hex_str[0] == '#') {
        hex_str = hex_str.substr(1);
    }

    if(hex_str.length() == 6) {
        sscanf(hex_str.c_str(), "%02x%02x%02x", &color->r, &color->g, &color->b);
        color->a = 255;
    }
    else if(hex_str.length() == 8) {
        sscanf(hex_str.c_str(), "%02x%02x%02x%02x", &color->r, &color->g, &color->b, &color->a);
    }
    else {
        log(LogLevel::ERROR, "Invalid hex string: %s", hex_str.c_str());
    }
}
