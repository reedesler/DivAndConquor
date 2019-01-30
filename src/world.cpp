//
// Created by Dmitry on 2019-01-25.
//

#include "world.h"

World::World(int w, int h, Camera *camera) : camera(camera) {
    this->tilemap.resize(w, std::vector<int>(h, 0));
}

World::~World() = default;

void World::update() {
    camera->update();
}

void World::draw(DrawContext *dc) {
    camera->draw(dc);
    camera->drawRect({50, 50, 100, 100}, {0, 255, 255, 255});
    camera->drawRect({75, 0, 50, 50}, {0, 255, 0, 0});
}
