#include <stdio.h>

#include "pda.h"
#include "rendersys.h"

int main() {
    //TODO: More initialization work
    setvbuf(stdout, NULL, _IOLBF, 0);

    init_render();

    while(1) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        return 0;
                    }
                    break;
            }
        }

        set_render_color(0, 0, 0, 255);
        SDL_RenderClear(renderer);

        set_render_color(255, 255, 255, 0);

        SDL_Point sidebar_poly[] = {
            {100, 0},
            {100, 200},
            {50, 150},
            {0, 150},
            {50, 150},
            {100, 200},
            {135, 235},
            {135, 365},
            {50, 450},
            {50, 500},
            {0, 500},
            {175, 500},
            {200, 525},
            {200, 600}
        };
        int sidebar_poly_len = sizeof(sidebar_poly) / sizeof(sidebar_poly[0]);

        draw_polyline(sidebar_poly, sidebar_poly_len);

        SDL_RenderPresent(renderer);

    }

}
