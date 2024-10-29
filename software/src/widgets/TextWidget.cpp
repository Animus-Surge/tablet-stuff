#include "objects/font.h"
#include "util/logger.h"

#include <SDL2/SDL_ttf.h>

void TextWidget::_reset_graphics_objects(SDL_Renderer* renderer) {
    //Free the old texture, if it exists
    if(this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }

    //Check if the font is set
    if(!this->font) {
        log(LogLevel::ERROR, "Font not set for TextWidget");
        return;
    }

    //Check if the text is set
    if(this->text.empty()) {
        log(LogLevel::ERROR, "Text not set for TextWidget");
        return;
    }

    //Render the text to a surface
    SDL_Surface* surface = TTF_RenderText_Solid(this->font, this->text.c_str(), this->color);
    if(!surface) {
        log(LogLevel::ERROR, "Failed to render text: %s", TTF_GetError());
        return;
    }

    //Create a texture from the surface
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(!this->texture) {
        log(LogLevel::ERROR, "Failed to create texture from surface: %s", SDL_GetError());
        return;
    }

    //Free the surface
    SDL_FreeSurface(surface);
}

void TextWidget::init() {
}

void TextWidget::event(SDL_Event* event) {
}

void TextWidget::update() {
}

void TextWidget::fixedUpdate(float dt) {
}

void TextWidget::render(SDL_Renderer* renderer) {
    if(!this->visible) {
        return;
    }

    if(this->update_texture) {
        this->_reset_graphics_objects(renderer);
        this->update_texture = false;
    }

    if(!this->texture) {
        log(LogLevel::ERROR, "No texture set for TextWidget");
        return;
    }

    SDL_Rect dest = {this->position.x, this->position.y, 0, 0};
    SDL_QueryTexture(this->texture, nullptr, nullptr, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, this->texture, nullptr, &dest);
}

void TextWidget::clean() {
    if(this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}
