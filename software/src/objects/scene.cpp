#include "scene_manager.h"

Scene::~Scene() {
    for (auto& object : objects) {
        delete object;
    }
}

void Scene::init() {

}
