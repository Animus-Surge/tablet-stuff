#include "objects/font.h"
#include "objects/scene.h"
#include "objects/widget.h"
#include "util/logger.h"
#include "util/util.h"

#include <fstream>

#include <SDL2/SDL_ttf.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

//Loads a scene from a file
Scene* load_scene(const char* path) {
    std::ifstream file(path);

    if(!file.is_open()) {
        log(LogLevel::ERROR, "Failed to open file: %s", path);
        return new Scene(); //Return an empty scene
    }

    log(LogLevel::INFO, "Loading scene from file: %s", path);

    Scene* scene = new Scene();

    json j;
    file >> j;

    scene->set_name(j["scene_name"]);

    //Load the widgets
    for(auto& widget : j["widgets"]) {
        //TODO: type validation

        //Check for required fields {name, type}
        if(!contains_keys(widget, {"name", "type"})) {
            log(LogLevel::ERROR, "Widget missing required fields");
            continue;
        }

        std::string type = widget["type"];
        std::string name = widget["name"];

        if (type == "point") {
            PointWidget* pointwidget = new PointWidget();

            //Required fields: color, position
            if(!contains_keys(widget, {"color", "position"})) {
                log(LogLevel::ERROR, "Point widget missing required fields");
                continue;
            }

            //Set the color
            SDL_Color color;
            if(widget["color"].is_string()) {
                hex_to_rgb(widget["color"], &color);
            }
            else {
                from_json(widget["color"], color);
            }
            pointwidget->set_color(color);
            
            //Set the position
            SDL_Point position = widget["position"];
            pointwidget->set_point(position);

            scene->add_widget(name, pointwidget);
        }
        else if(type == "line") {
            LineWidget* linewidget = new LineWidget();

            if(!contains_keys(widget, {"color", "start", "end"})) {
                log(LogLevel::ERROR, "Line widget missing required fields");
                continue;
            }

            SDL_Color color;
            if(widget["color"].is_string()) {
                hex_to_rgb(widget["color"], &color);
            }
            else {
                from_json(widget["color"], color);
            }
            linewidget->set_color(color);

            SDL_Point start = widget["start"];
            SDL_Point end = widget["end"];
            linewidget->set_start(start);
            linewidget->set_end(end);

            //Optional fields
            if(contains_key(widget, "thickness")) {
                linewidget->set_thickness(widget["thickness"]);
            }

            scene->add_widget(name, linewidget);
        }
        else if(type == "polyline") {
            PolylineWidget* polylinewidget = new PolylineWidget();

            if(!contains_keys(widget, {"color", "points", "connect"})) {
                log(LogLevel::ERROR, "Polyline Widget missing required fields");
                continue;
            }

            SDL_Color color;
            if(widget["color"].is_string()) {
                hex_to_rgb(widget["color"], &color);
            } else {
                color = widget["color"];
            }
            polylinewidget->set_color(color);

            polylinewidget->set_connect(widget["connect"]);

            for(auto& point : widget["points"]) {
                SDL_Point p = point;
                polylinewidget->add_point(p);
            }

            if(contains_key(widget, "thickness")) {
                polylinewidget->set_thickness(widget["thickness"]);
            }
            if(contains_key(widget, "fill")) {
                polylinewidget->set_fill(widget["fill"]);
                polylinewidget->set_thickness(1);

                if(contains_key(widget, "fill_color")) {
                    polylinewidget->set_fill_color(widget["fill_color"]);
                } else {
                    polylinewidget->set_fill_color(polylinewidget->get_color());
                }
            }

            scene->add_widget(name, polylinewidget);
        }
        else if(type == "rect") {
            RectangleWidget* rectanglewidget = new RectangleWidget();

            if(!contains_keys(widget, {"position", "width", "height"})) {
                log(LogLevel::ERROR, "Rectangle widget missing required fields");
                continue;
            }

            SDL_Point position = widget["position"];
            int width = widget["width"];
            int height = widget["height"];

            SDL_Rect rect = {position.x, position.y, width, height};
            rectanglewidget->set_rect(rect);

            if(contains_key(widget, "thickness")) {
                rectanglewidget->set_thickness(widget["thickness"]);
            }

            if(contains_key(widget, "fill")) {
                rectanglewidget->set_fill(widget["fill"]);
                rectanglewidget->set_thickness(1);

                if(contains_key(widget, "fill_color")) {
                    rectanglewidget->set_fill_color(widget["fill_color"]);
                } else {
                    rectanglewidget->set_fill_color(rectanglewidget->get_color());
                }
            }

            scene->add_widget(name, rectanglewidget);
        }
        else if(type == "circle") {
            CircleWidget* circlewidget = new CircleWidget();

            if(!contains_keys(widget, {"color", "position", "radius"})) {
                log(LogLevel::ERROR, "Circle widget missing required fields");
                continue;
            }

            SDL_Color color;
            if(widget["color"].is_string()) {
                hex_to_rgb(widget["color"], &color);
            } else {
                color = widget["color"];
            }
            circlewidget->set_color(color);

            circlewidget->set_position(widget["position"]);

            circlewidget->set_radius(widget["radius"]);

            if(contains_key(widget, "thickness")) {
                circlewidget->set_thickness(widget["thickness"]);
            }

            if(contains_key(widget, "fill")) {
                circlewidget->set_fill(widget["fill"]);
                circlewidget->set_thickness(1);

                if(contains_key(widget, "fill_color")) {
                    circlewidget->set_fill_color(widget["fill_color"]);
                } else {
                    circlewidget->set_fill_color(circlewidget->get_color());
                }
            }

            scene->add_widget(name, circlewidget);
        }
        else if(type == "ellipse") {
            EllipseWidget* ellipsewidget = new EllipseWidget();

            if(!contains_keys(widget, {"color", "position", "rx", "ry"})) {
                log(LogLevel::ERROR, "Ellipse widget missing required fields");
                continue;
            }

            SDL_Color color;
            if(widget["color"].is_string()) {
                hex_to_rgb(widget["color"], &color);
            } else {
                color = widget["color"];
            }
            ellipsewidget->set_color(color);

            ellipsewidget->set_position(widget["position"]);

            ellipsewidget->set_rx(widget["rx"]);
            ellipsewidget->set_ry(widget["ry"]);

            if(contains_key(widget, "thickness")) {
                ellipsewidget->set_thickness(widget["thickness"]);
            }

            if(contains_key(widget, "fill")) {
                ellipsewidget->set_fill(widget["fill"]);
                ellipsewidget->set_thickness(1);

                if(contains_key(widget, "fill_color")) {
                    ellipsewidget->set_fill_color(widget["fill_color"]);
                } else {
                    ellipsewidget->set_fill_color(ellipsewidget->get_color());
                }
            }

            scene->add_widget(name, ellipsewidget);
        }
        //TODO: images (svg, png)

        else if(type == "text") {
            TextWidget* textwidget = new TextWidget();

            if(!contains_keys(widget, {"color", "position", "text", "font", "size"})) {
                log(LogLevel::ERROR, "Text widget missing required keys");
                continue;
            }

            SDL_Color color;
            if(widget["color"].is_string()) {
                hex_to_rgb(widget["color"], &color);
            } else {
                color = widget["color"];
            }
            textwidget->set_color(color);

            std::string font_filepath = widget["font"];

            textwidget->set_position(widget["position"]);
            textwidget->set_text(widget["text"]);
            textwidget->set_font(TTF_OpenFont(font_filepath.c_str(), widget["size"]));

            scene->add_widget(name, textwidget);
        }
        //...
        else {
            log(LogLevel::ERROR, "Unknown widget type: %s", type);
            continue;
        }
    }

    return scene;
}
