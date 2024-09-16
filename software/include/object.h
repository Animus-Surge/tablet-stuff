#pragma once

/*
pda object.h

Object definitions
*/

#include <functional>
#include <map>
#include <string>

class Object {
public:
    Object(const char* name, std::function<void> initfn);
    ~Object();

    void render();
};
