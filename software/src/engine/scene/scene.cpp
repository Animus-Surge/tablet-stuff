#include "objects/scene.h"

void Scene::handleEvent(SDL_Event* event) {
    for(auto& [name, widget] : widgets) {
        widget->event(event);
    }
}

void Scene::update() {
    for(auto& [name, widget] : widgets) {
        widget->update();
    }
}

void Scene::fixedUpdate(float dt) {
    //Do nothing (TODO)
}

void Scene::render(SDL_Renderer* renderer) {
    for(auto& [name, widget] : widgets) {
        widget->render(renderer);
    }
}

void Scene::clean() {
    widgets.clear(); //TODO: maybe delete widgets first?
}


