#pragma once

/**
 * pda objects/inputwidget.h
 * Base inputs
 */

#include "objects/widget.h"

#include <vector>
#include <map>

#include <SDL2/SDL.h>

//wip

//Base interactables

class BaseClickableWidget : public BaseWidget {

    void onclick();

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void fixedUpdate(float dt) = 0;
    virtual void render(SDL_Renderer* renderer) = 0;
    virtual void clean() = 0;
    
    void event(SDL_Event* event) override;

};

class BaseTextfieldWidget : public BaseWidget {
private:
    SDL_Point position;
    char input[256];
    bool focused = false;

public:
    void _handle_text_input();

};

//Container classes (forms, button groups, etc.)

class FormWidget : public BaseWidget {
//TODO: impl
};

class ButtonGroup : public BaseWidget {
//TODO: impl
};

//Default theme interactables

/*
 * TODO: impl
 * - Button
 * - Polygon button?
 * - Radio button
 * - Checkbox
 * - Text box
 * - Text field?
 * - Dropdown
 */


