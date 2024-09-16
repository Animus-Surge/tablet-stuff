#include "app.h"
#include "rendersys.h"

void init() {
    init(1024, 600, "Test Window");

    run();

    shutdown();
}
