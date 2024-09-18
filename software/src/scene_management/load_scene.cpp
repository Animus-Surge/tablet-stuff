#include "scene_manager.h"

#include <fstream>

#include <json/json.h>

Scene* load_scene(const char *path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return NULL;
    }

    return NULL;
}
