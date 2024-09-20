#include "scene_manager.h"

#include <cstdio>
#include <fstream>

Scene* current_scene = NULL;

Scene* load_scne(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        printf("Failed to open %s", path);
        return NULL;
    }

    return NULL;
}
