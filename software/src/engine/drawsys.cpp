#include "engine/drawsys.h"

SDL_Color draw_color = {255, 255, 255, 255};

// Basic drawing functions

void point(SDL_Renderer* renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void line(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int thickness) {
    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void pline(SDL_Renderer* renderer, SDL_Point* points, int count, int thickness) {
    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    SDL_RenderDrawLines(renderer, points, count);
}

void rect(SDL_Renderer* renderer, int x, int y, int w, int h, int thickness) {
    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderDrawRect(renderer, &rect);
}

void polygon(SDL_Renderer* renderer, SDL_Point* points, int count, int thickness) {
    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    SDL_RenderDrawLines(renderer, points, count);
    SDL_RenderDrawLine(renderer, points[count - 1].x, points[count - 1].y, points[0].x, points[0].y);
}

void circle(SDL_Renderer* renderer, int x, int y, int r, int thickness) {
    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    int x1 = 0;
    int y1 = r;
    int p = 3 - 2 * r;
    while (x1 <= y1) {
        SDL_RenderDrawPoint(renderer, x + x1, y + y1);
        SDL_RenderDrawPoint(renderer, x + x1, y - y1);
        SDL_RenderDrawPoint(renderer, x - x1, y + y1);
        SDL_RenderDrawPoint(renderer, x - x1, y - y1);
        SDL_RenderDrawPoint(renderer, x + y1, y + x1);
        SDL_RenderDrawPoint(renderer, x + y1, y - x1);
        SDL_RenderDrawPoint(renderer, x - y1, y + x1);
        SDL_RenderDrawPoint(renderer, x - y1, y - x1);
        if (p < 0) {
            p += 4 * x1 + 6;
        } else {
            p += 4 * (x1 - y1) + 10;
            y1--;
        }
        x1++;
    }
}

void ellipse(SDL_Renderer* renderer, int x, int y, int rx, int ry, int thickness) {
    //case: rx=ry
    if (rx == ry) {
        circle(renderer, x, y, rx, thickness);
        return;
    }

    SDL_SetRenderDrawColor(renderer, draw_color.r, draw_color.g, draw_color.b, draw_color.a);
    int x1 = 0;
    int y1 = ry;
    int rx2 = rx * rx;
    int ry2 = ry * ry;
    int p = ry2 - rx2 * ry + rx2 / 4;
    while (2 * ry2 * x1 < 2 * rx2 * y1) {
        SDL_RenderDrawPoint(renderer, x + x1, y + y1);
        SDL_RenderDrawPoint(renderer, x + x1, y - y1);
        SDL_RenderDrawPoint(renderer, x - x1, y + y1);
        SDL_RenderDrawPoint(renderer, x - x1, y - y1);
        if (p < 0) {
            p += 2 * ry2 * (2 * x1 + 3);
        } else {
            p += 2 * ry2 * (2 * x1 + 3) + 4 * rx2 * (1 - y1);
            y1--;
        }
        x1++;
    }
    p = ry2 * (x1 + 1/2) * (x1 + 1/2) + rx2 * (y1 - 1) * (y1 - 1) - rx2 * ry2;
    while (y1 >= 0) {
        SDL_RenderDrawPoint(renderer, x + x1, y + y1);
        SDL_RenderDrawPoint(renderer, x + x1, y - y1);
        SDL_RenderDrawPoint(renderer, x - x1, y + y1);
        SDL_RenderDrawPoint(renderer, x - x1, y - y1);
        if (p > 0) {
            p += 4 * rx2 * (1 - y1);
        } else {
            p += 2 * ry2 * (2 * x1 + 2) + 4 * rx2 * (1 - y1);
            x1++;
        }
        y1--;
    }
}

// Curves

void bezier(SDL_Renderer* renderer, SDL_Point start, SDL_Point control1, SDL_Point control2, SDL_Point end, float step) {
    //TODO: implement w/ linear interpolation function (will define in util/util.h)
}
