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
        if(!contains_keys(widget, {"name", "type"})) {
            log(LogLevel::ERROR, "Widget missing required fields");
            continue;
        }

        std::string type = widget["type"];

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
                color = widget["color"];
            }
            pointwidget->set_color(color);
            
            //Set the position
            SDL_Point position = widget["position"];
            pointwidget->set_point(position);
        }
        else if(type == "line") {
            LineWidget* line = new LineWidget();
        }
        else if(type == "polyline") {
            PolylineWidget* polylinewidget = new PolylineWidget();
        }
        else if(type == "rect") {
            RectangleWidget* rectanglewidget = new RectangleWidget();
        }
        else if(type == "circle") {
            CircleWidget* circlewidget = new CircleWidget();
        }
        else if(type == "ellipse") {
            EllipseWidget* ellipsewidget = new EllipseWidget();
        }
        //TODO: images (svg, png)

        else if(type == "text") {
            TextWidget* textwidget = new TextWidget();
        }
        //...
        else {
            log(LogLevel::ERROR, "Unknown widget type: %s", type);
            continue;
        }
    }

    return scene;
}
