#include "soareds.h"

#include "rendersys.h"

void header_render() {
    set_render_color(0, 255, 255, 255);

    draw_line(200, 0, 175, 25);
    draw_line(175, 25, 0, 25);
}
