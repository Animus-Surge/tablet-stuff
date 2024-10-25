#pragma once

/**
 * Base scene class.
 */

#include <vector>

class Scene {
protected:

public:
    virtual void init() = 0;
    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean() = 0;
};
