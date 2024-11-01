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

        //Check for required fields {name, type}
        if(widget.find("name") == widget.end() || widget.find("type") == widget.end()) {
            log(LogLevel::ERROR, "Widget missing required fields: {name, type}");
            continue;
        }

        bool valid = true;

        if(!widget["type"].is_string()) {
            log(LogLevel::ERROR, "Field 'type' must be a string");
            valid = false;
        }
        if(!widget["name"].is_string()) {
            log(LogLevel::ERROR, "Field 'name' must be a string");
            valid = false;
        }

        if(!valid) {
            continue;
        }

        std::string type = widget["type"];

        if (type == "point") {
            PointWidget* point = new PointWidget();

            if(widget.find("color") == widget.end() || widget.find("point") == widget.end()) {
                log(LogLevel::ERROR, "Point widget missing required fields: {color, point}");
                delete point;
                continue;
            }
            
            if(widget["color"].is_string()) {
                std::string hex = widget["color"];
                SDL_Color color;
                hex_to_rgb(hex.c_str(), &color);
                point->set_color(color);
            } else if(widget["color"].is_object()) {
                SDL_Color color;
                from_json(widget["color"], color);
                point->set_color(color);
            } else {
                log(LogLevel::ERROR, "Point widget color must be an object (rgb[a]) or a string (hex)");
                valid = false
            }

            if(widget["point"].is_object()) {
                SDL_Point point;
                from_json(widget["point"], point);
                point->set_point(point);
            } else {
                log(LogLevel::ERROR, "Point widget point must be an object {x, y}");
                valid = false;
            }

            if(!valid) {
                delete point;
                continue;
            }

            scene->add_widget(widget["name"], point);
        }
        else if(type == "line") {
            LineWidget* line = new LineWidget();
            
            if(widget.find("color") == widget.end() || widget.find("start") == widget.end() || widget.find("end") == widget.end() || widget.find("thickness") == widget.end()) {
                log(LogLevel::ERROR, "Line widget missing required fields: {color, start, end, thickness}");
                continue;
            }

            //Color check
            if(widget["color"].is_object()) {
                SDL_Color color;
                from_json(widget["color"], color);
                line->set_color(color);
            } else if(widget["color"].is_string()) {
                std::string hex = widget["color"];
                SDL_Color color;
                hex_to_rgb(hex.c_str(), &color);
                line->set_color(color);
            } else {
                log(LogLevel::ERROR, "Line widget color must be an object (rgb[a]) or a string (hex)");
                continue;
            }

            if(widget["start"].is_object()) {
                SDL_Point start;
                from_json(widget["start"], start);
                line->set_start(start);
            } else {
                log(LogLevel::ERROR, "Line widget start must be an object {x, y}");
                continue;
            }

            if(widget["end"].is_object()) {
                SDL_Point end;
                from_json(widget["end"], end);
                line->set_end(end);
            } else {
                log(LogLevel::ERROR, "Line widget end must be an object {x, y}");
                continue;
            }
            
            if(widget["thickness"].is_number()) {
                line->set_thickness(widget["thickness"]);
            } else {
                log(LogLevel::ERROR, "Line widget thickness must be a number");
                continue;
            }

            scene->add_widget(widget["name"], line);
        }
        else if(type == "polyline") {
            PolylineWidget* polyline = new PolylineWidget();

            polyline->set_color(widget["color"]["r"], widget["color"]["g"], widget["color"]["b"], widget["color"]["a"]);
            
            polyline->set_connect(widget["connect"]);
            polyline->set_thickness(widget["thickness"]);

            for(int i = 0; i < widget["point_ct"]; i++) {
                polyline->add_point({widget["points"][i]["x"], widget["points"][i]["y"]});
            }

            scene->add_widget(widget["name"], polyline);
        }
            
        else if(type == "text") {
            TextWidget* text = new TextWidget();

            std::string font_path = widget["font"]["path"];
            
            text->set_color(widget["color"]["r"], widget["color"]["g"], widget["color"]["b"], widget["color"]["a"]);
            text->set_position(widget["position"]["x"], widget["position"]["y"]);
            text->set_text(widget["text"]);
            text->set_font(TTF_OpenFont(font_path.c_str(), widget["font"]["size"]));

            scene->add_widget(widget["name"], text);
        }
        //...
        else {
            log(LogLevel::ERROR, "Unknown widget type: %s", type);
            continue;
        }
    }

    return scene;
}
