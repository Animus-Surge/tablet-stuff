#include "objects/scene.h"
#include "objects/widget.h"

void BasicTestScene::init() {
    PointWidget* point = new PointWidget();
    point->set_point(100, 100);
    point->set_color(255, 0, 0, 255);
    point->set_position(100, 100);
    add_widget("point", point);
}
