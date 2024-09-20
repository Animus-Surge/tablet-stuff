#include "object.h"
#include <cstdio>

Object::Object(const char* name, std::function<void()> initfn) {
    this->name = name;
    initfn();
}

Object::~Object() {}

void Object::update() {
    for (auto component : components) {
        component->update();
    }
}

void Object::render() {
    for (auto* component : components) {
        component->render();
    }
}
