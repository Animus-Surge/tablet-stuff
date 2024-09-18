#pragma once

/*
pda scene_manager.h

Scene systems and scene object definitions
*/

#include "object.h"
#include <functional>
#include <map>
#include <vector>

class Scene {
protected:
    std::vector<Object*> objects;

public:
    Scene() = default;
    ~Scene();

    void init();

    void add_object(Object* object) {
        objects.push_back(object);
    }

    void remove_object(Object* object) {
        objects.erase(std::remove(objects.begin(), objects.end(), object), objects.end());
    }

    void clear_objects() {
        objects.clear();
    }

    void update_objects() {
        for (auto object : objects) {

        }
    }

    void draw_objects() {
        for (auto object : objects) {
            object->render();
        }
    }
};

extern Scene current_scene;

inline void set_scene(Scene scene) {
    current_scene = scene;
}

Scene* load_scene(const char* path);
inline Scene* create_empty_scene() {
    return new Scene();
}
