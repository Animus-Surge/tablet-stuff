#include "algo.h"

float cross_product(SDL_Point p1, SDL_Point p2) {
    return p1.x * p2.y - p1.y * p2.x;
}

int winding_number(SDL_Point *points, int num) {
    int wn = 0;
    for (int i = 0; i < num; i++) {
        SDL_Point p1 = points[i];
        SDL_Point p2 = points[(i + 1) % num];
        if (p1.y <= 0) {
            if (p2.y > 0) {
                if (cross_product(p1, p2) > 0) {
                    wn++;
                }
            }
        } else if (p1.y > 0) {
            if (p2.y <= 0) {
                if (cross_product(p1, p2) < 0) {
                    wn--;
                }
            }
        }
    }
    return wn;
}
