#include <stdio.h>

#include "pda.h"
#include "rendersys.h"

int main() {
    //TODO: More initialization work
    setvbuf(stdout, NULL, _IOLBF, 0);

    init_render();

    int running = 1;

    while(running) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                        break;
                    }
                    break;
            }
        }

        set_render_color(0, 0, 0, 255);
        SDL_RenderClear(renderer);

        set_render_color(255, 255, 255, 0);

        SDL_Point test_poly[] = {
            {10, 200},
            {30, 220},
            {30, 320},
            {10, 340}
        };
        int test_poly_len = sizeof(test_poly) / sizeof(test_poly[0]);

        SDL_Point test_poly2[] = {
            {40, 200},
            {60, 220},
            {60, 320},
            {40, 340}
        };
        int test_poly2_len = sizeof(test_poly2) / sizeof(test_poly2[0]);

        //Test drawing
        draw_point(10, 10);

        draw_line(20, 10, 100, 90);

        draw_rect(110, 10, 80, 80);

        draw_polyline(test_poly, test_poly_len);

        draw_circle(260, 50, 40);

        draw_ellipse(360, 50, 50, 30);

        fill_polygon(test_poly2, test_poly2_len);

        SDL_RenderPresent(renderer);


    }

}
