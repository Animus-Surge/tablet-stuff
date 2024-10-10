#include "font.h"
#include "rendersys.h"

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL_render.h>

void render_text(const char *nick, const char *text, SDL_Point pos, SDL_Color color) {
    TTF_Font* font = get_font(nick);
    if(font == NULL) {
        return;
    }

    SDL_Surface* text_surf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture* text_t = SDL_CreateTextureFromSurface(renderer, text_surf);

    SDL_Rect text_transform = {pos.x, pos.y, text_surf->w, text_surf->h};
    SDL_RenderCopy(renderer, text_t, NULL, &text_transform);

    SDL_DestroyTexture(text_t);
    SDL_FreeSurface(text_surf);
}
