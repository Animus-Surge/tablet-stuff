#include "rendersys.h"
#include <SDL_render.h>

#include <cmath>

#define DEGREE_STEP 1

void render_point(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}
void render_point(SDL_Point point) {
    render_point(point.x, point.y);
}

void render_line(int x1, int y1, int x2, int y2, int thickness) {
    //Ignore thickness for now
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

#ifdef RENDER_LINE_THICKNESS
    int half_thickness = floor(thickness / 2);

    //First, slope
    float slope = (float)(y2 - y1) / (x2 - x1);
    float perp_slope = -1 / slope;

    //Now we need to get the four points along the perpendicular slope


#endif
}
void render_line(SDL_Point p1, SDL_Point p2, int thickness) {
    render_line(p1.x, p1.y, p2.x, p2.y, thickness);
}

void render_circle(int x, int y, int r, int thickness) {
    int rd = 0;

    while (rd < 360) {
        int x1 = x + r * cos(rd * M_PI / 180);
        int y1 = y + r * sin(rd * M_PI / 180);
        rd += DEGREE_STEP;
        int x2 = x + r * cos(rd * M_PI / 180);
        int y2 = y + r * sin(rd * M_PI / 180);
        render_line(x1, y1, x2, y2, thickness);
    }
}

void render_circle(SDL_Point point, int r, int thickness) {
    render_circle(point.x, point.y, r, thickness);
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

void render_polyline(SDL_Point points[], int num_points, int thickness) {
    for (int i = 0; i < num_points - 1; i++) {
        render_line(points[i], points[i + 1], thickness);
    }
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
    //TODO
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
