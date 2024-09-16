#pragma once

/*
pda scene_manager.h

Scene systems
*/

#include <functional>
#include <map>
#include <vector>


struct scene {
    //TODO: components

    std::function<void()> initfn;
    std::function<void()> renderfn;
};

extern struct scene current_scene;

void set_scene(struct scene new_scene);

void animate_scene_in();
void animate_scene_out();
