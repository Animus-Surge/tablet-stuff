#include "objects/scene.h"


//TODO: implement
void load_scene(const char* path) {
}

Scene::handleEvent(SDL_Event* event) {
    for (auto& widget : widgets) {
        widget->event(event);
    }
}

Scene::update() {
    for (auto& widget : widgets) {
        widget->update();
    }
}

Scene::render(SDL_Renderer* renderer) {
    for (auto& widget : widgets) {
        widget->render(SDL_Renderer* renderer);
    }
}

Scene::clean() {
    for (auto& widget : widgets) {
        widget->clean();
        delete widget;
    }
}


