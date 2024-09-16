#include "rendersys.h"
#include <SDL_render.h>

void render_point(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}
void render_point(SDL_Point point) {
    render_point(point.x, point.y);
}

void render_line(int x1, int y1, int x2, int y2, int thickness) {
    for (int i = 0; i < thickness; i++) {
        SDL_RenderDrawLine(renderer, x1, y1 + i, x2, y2 + i);
    }
}
void render_line(SDL_Point p1, SDL_Point p2, int thickness) {
    render_line(p1.x, p1.y, p2.x, p2.y, thickness);
}

void render_circle(int x, int y, int r, int thickness) {
    for (int i = 0; i < thickness; i++) {
        for (int j = 0; j < r; j++) {
            int h = (int)sqrt(r * r - j * j);
            SDL_RenderDrawLine(renderer, x - h + i, y + j, x + h + i, y + j);
            SDL_RenderDrawLine(renderer, x - h + i, y - j, x + h + i, y - j);
        }
    }
}

void render_rect(int x, int y, int w, int h, int thickness) {
    for (int i = 0; i < thickness; i++) {
        SDL_Rect rect = {x - i, y - i, w + 2 * i, h + 2 * i};
        SDL_RenderDrawRect(renderer, &rect);
    }
}
void render_rect(SDL_Rect rect, int thickness) {
    render_rect(rect.x, rect.y, rect.w, rect.h, thickness);
}

void render_polygon(SDL_Point points[], int num_points, int thickness) {
    for (int i = 0; i < num_points - 1; i++) {
        render_line(points[i], points[i + 1], thickness);
    }
    render_line(points[num_points - 1], points[0], thickness);
}


//Fill functions
void fill_rect(int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    fill_rect(rect);
}
void fill_rect(SDL_Rect rect) {
    SDL_RenderFillRect(renderer, &rect);
}

void fill_circle (int x, int y, int r) {
    for (int i = 0; i < r; i++) {
        int h = (int)sqrt(r * r - i * i);
        SDL_RenderDrawLine(renderer, x - h, y + i, x + h, y + i);
        SDL_RenderDrawLine(renderer, x - h, y - i, x + h, y - i);
    }
}

void fill_circle(SDL_Point pos, int r) {
    fill_circle(pos.x, pos.y, r);
}

void fill_polygon(SDL_Point points[], int num_points) {
    //Draw outline
    render_polygon(points, num_points, 1);

    //Fill using scanline algorithm
    int min_y = points[0].y;
    int max_y = points[0].y;
    for (int i = 1; i < num_points; i++) {
        if (points[i].y < min_y) {
            min_y = points[i].y;
        }
        if (points[i].y > max_y) {
            max_y = points[i].y;
        }
    }

    for (int y = min_y; y <= max_y; y++) {
        int intersections = 0;
        for (int i = 0; i < num_points; i++) {
            int j = (i + 1) % num_points;
            if ((points[i].y <= y && points[j].y > y) || (points[j].y <= y && points[i].y > y)) {
                float x = (float)(points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x;
                if (x <= points[i].x) {
                    intersections++;
                }
            }
        }
        for (int i = 0; i < num_points; i++) {
            int j = (i + 1) % num_points;
            if (points[i].y == y && points[j].y == y) {
                if (points[i].x < points[j].x) {
                    intersections++;
                }
            }
        }
        for (int i = 0; i < intersections; i += 2) {
            render_line((int)points[i].x, y, (int)points[i + 1].x, y, 1);
        }
    }
}
