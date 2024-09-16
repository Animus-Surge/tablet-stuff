#include "modules/ttf_mod.h"
#include <SDL2/SDL_ttf.h>

bool initialized = false;
std::map<std::string, TTF_Font*> fonts;

void ttf_init() {

}

void ttf_quit() {

}

TTF_Font* ttf_load_font(const char* path, int size) {

    return NULL;
}
