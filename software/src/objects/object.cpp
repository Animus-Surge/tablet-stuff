#include "object.h"

Object::Object(const char* name, std::function<void()> initfn) {
    this->name = name;
    initfn();
}

Object::~Object() {}

void Object::render() {
    for (auto i = components.begin(); i != components.end(); i++) {
        i->render(this->position);
    }
}
