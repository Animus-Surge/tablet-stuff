#include <stdio.h>

#include "pda.h"
#include "rendersys.h"

#include "font.h"

#include "soareds.h"

int main() {
    //TODO: More initialization work
    setvbuf(stdout, NULL, _IOLBF, 0);

    init_render();

    int running = 1;

    int screen_idx = 1; // TODO: move to enum
    bool show_header = true;

    // Begin loading fonts

    //Font loading stuff, TESTING ONLY
    bool success = true;


    //TODO: variable font size (implement research/font in main)
    if(!load_font("resources/Iceberg-Regular.ttf", "iceberg-24", 24)) {
        printf("Failed to load font 'iceberg-24'\n");
        success = false;
    }

    if(!load_font("resources/Iceberg-Regular.ttf", "iceberg-20", 20)) {
        printf("Failed to load font 'iceberg-20'\n");
        success = false;
    }

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

        if(success) {
            render_text("iceberg-24", "SYSTEM MENU", {5, 3}, {255, 255, 255, 255});
            render_text("iceberg-20", "USS LIGHTWAVE \xB7 NX-108000", {450, 450}, {255, 255, 255, 255});
        }

        SDL_RenderPresent(renderer);
    }

    destroy_font("iceberg-24");
    destroy_font("iceberg-20");

    shutdown();
}
