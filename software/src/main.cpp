#include <stdio.h>

#include "pda.h"
#include "rendersys.h"

#include "soareds.h"

int main() {
    //TODO: More initialization work
    setvbuf(stdout, NULL, _IOLBF, 0);

    init_render();

    int running = 1;

    int screen_idx = 1; // TODO: move to enum
    bool show_header = true;

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

        // Render system stuff, main header, etc.
        if (show_header) {
            header_render();
        }

        SDL_RenderPresent(renderer);


    }

}
