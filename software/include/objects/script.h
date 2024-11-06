#pragma once

/**
 * pda include/script.h
 * Scripting objects and utility functions
 */

#include <lua.hpp>

class LuaScript {

    LuaState* lstate;
    std::string srcfile;

public:

    void call_fn(const char* func);

};
