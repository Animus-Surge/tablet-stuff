#include "objects/scene.h"
#include "objects/widget.h"
#include "util/logger.h"

#include <fstream>

//Loads a scene from a file
Scene* load_scene(const char* path) {
    std::ifstream file(path);

    if(!file.is_open()) {
        log_error("Failed to open file: %s", path);
        return new Scene(); //Return an empty scene
    }

    Scene* scene = new Scene();

    return scene;
}
