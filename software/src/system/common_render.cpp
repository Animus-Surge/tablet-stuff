#include "pda.h"
#include "soareds.h"

#include "rendersys.h"

void header_render() {
    set_render_color(255, 255, 255, 255);

    SDL_Point header_pts[] = {
        {160, 40},
        {400, 40},
        {440, 0},
        {405, 35},
        {645, 35},
        {610, 0},
        {660, 50},
        {1024, 50},
    };

    SDL_Point sidebar_pts[] = {
        {200, 0},
        {150, 50},
        {0, 50},
        {100, 50},
        {100, 250},
        {80, 270},
        {0, 270},
        {80, 270},
        {80, 500},
        {120, 540},
        {120, 600}
    };
    int side_len = ARRAY_SIZE(sidebar_pts);
    int head_len = ARRAY_SIZE(header_pts);

    draw_polyline(sidebar_pts, side_len);
    draw_polyline(header_pts, head_len);

    draw_line(800, 0, 850, 50);
}
