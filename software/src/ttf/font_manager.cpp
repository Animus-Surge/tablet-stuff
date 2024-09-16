#include "modules/ttf_mod.h"
#include <SDL_ttf.h>

bool initialized = false;
std::map<std::string, TTF_Font*> fonts;

void ttf_init() {
    initialized = true;
    TTF_Init();
}

void ttf_quit() {
    TTF_Quit();
}

TTF_Font* ttf_load_font(const char* path, int size) {
    TTF_Font* font = TTF_OpenFont(path, size);

    return font;
}
