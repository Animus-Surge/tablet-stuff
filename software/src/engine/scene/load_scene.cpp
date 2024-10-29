#include "objects/font.h"
#include "objects/scene.h"
#include "objects/widget.h"
#include "util/logger.h"

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
        std::string type = widget["type"];

        if (type == "point") {\
            PointWidget* point = new PointWidget();
            
            point->set_color(widget["color"]["r"], widget["color"]["g"], widget["color"]["b"], widget["color"]["a"]);
            point->set_point(widget["point"]["x"], widget["point"]["y"]);

            scene->add_widget(widget["name"], point);
        }
        else if(type == "line") {
            LineWidget* line = new LineWidget();
                
            line->set_color(widget["color"]["r"], widget["color"]["g"], widget["color"]["b"], widget["color"]["a"]);
            line->set_start(widget["start"]["x"], widget["start"]["y"]);
            line->set_end(widget["end"]["x"], widget["end"]["y"]);
            line->set_thickness(widget["thickness"]);

            scene->add_widget(widget["name"], line);
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
