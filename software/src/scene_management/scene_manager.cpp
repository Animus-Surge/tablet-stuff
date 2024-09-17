#include "scene_manager.h"

#include <cstdio>
#include <fstream>

Scene load_scne(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        printf("Failed to open %s", path);
        return Scene();
    }

    Scene scene;
    std::string line;



    return Scene();
}
