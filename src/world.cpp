//
// Created by Dmitry on 2019-01-25.
//
#include <fstream>

#include "world.h"
#include "PirateBoat.h"

World::World(int w, int h, Camera *camera) : camera(camera)
{
    this->tilemap.resize(w, std::vector<int>(h, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
}

World::~World() = default;

void World::update() {
    camera->update();
    for (auto go : gameObjects) {
        go->update();
    }
}

void World::draw(DrawContext *dc) {
    camera->draw(dc);
    for (int i = 0; i < 100; i++)
    {
        camera->drawRect({200 + 10 * i, 200, 10, 10}, {0, 255, 255, 255});
    }
    camera->drawRect({50, 50, 100, 100}, {0, 255, 255, 255});
    camera->drawRect({75, 0, 50, 50}, {0, 255, 0, 0});
}