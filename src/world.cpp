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
    dc->drawRect({static_cast<int>(round(0 - camera->x)), static_cast<int>(round(0 - camera->y)), 100, 100}, {255, 255, 255, 255});
}
