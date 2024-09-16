#pragma once

/*
pda scene_manager.h

Scene systems
*/

#include <vector>

struct scene {
    std::vector<void*> entities;

    void (*init)();
    void (*update)();
    void (*draw)();
    void (*exit)();
};

void scene_manager_init();
