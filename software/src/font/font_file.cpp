#include "font.h"

#include <cstdio>
#include <map>
#include <string>

#include <SDL2/SDL_ttf.h>

std::map<std::string, TTF_Font*> fontMap;

bool load_font(const char* filename, const char* nickname, int pt_size) {
    std::string nick_as_str(nickname);

    if (TTF_WasInit() == 0) {
        if(TTF_Init() != 0) {
            printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
            return false;
        }
    }

    if(fontMap.find(nick_as_str) != fontMap.end()) {
        printf("Font %s already exists and is loaded\n", nickname);
    }

    TTF_Font* font = TTF_OpenFont(filename, pt_size);

    if (font == NULL) {
        printf("Error loading font %s: %s\n", filename, TTF_GetError());
        return false;
    }

    fontMap[nick_as_str] = font;

    printf("Font loaded: %s - %s\n", filename, nickname);

    return true;
}

TTF_Font* get_font(const char* nick) {
    std::string nick_as_str(nick);

    if(fontMap.find(nick_as_str) == fontMap.end()) {
        printf("No font with name '%s'\n", nick);
        return NULL;
    }

    return fontMap[nick_as_str];
}

void destroy_font(const char *nick) {
    std::string nick_as_str(nick);

    //Case: font <nick> doesn't exist
    if(fontMap.find(nick_as_str) == fontMap.end()) {
        return;
    }

    fontMap.erase(nick_as_str);
}
