#pragma once

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include <string>

#include "objects/widget.h"

class TextWidget : public BaseWidget {
private:
    SDL_Texture* texture = nullptr;
    SDL_Point position = {0, 0};
    TTF_Font* font = nullptr;

    bool update_texture = true;

protected:
    std::string text = "";

    void _reset_graphics_objects(SDL_Renderer* renderer);

public:

    void set_position(SDL_Point position) {
        this->position = position;
    }
    void set_position(int x, int y) {
        this->position.x = x;
        this->position.y = y;
    }
    SDL_Point get_position() const {
        return position;
    }

    void set_font(TTF_Font* font) {
        this->font = font;
        this->update_texture = true;
    }
    TTF_Font* get_font() const {
        return this->font;
    }

    void set_text(const std::string& text) {
        this->text = text;
        this->update_texture = true;
    }
    std::string get_text() const {
        return text;
    }

    void init() override;
    void event(SDL_Event* event) override;
    void update() override;
    void fixedUpdate(float dt) override;
    void render(SDL_Renderer* renderer) override;
    void clean() override;
};
