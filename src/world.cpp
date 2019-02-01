//
// Created by Dmitry on 2019-01-25.
//
#include <fstream>

#include "world.h"
#include "PirateBoat.h"
#include "PlayerBoat.h"

World::World(int w, int h, Camera *camera) : camera(camera)
{
    this->tilemap.resize(w, std::vector<int>(h, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    gameObjects.push_back(new PirateBoat(0, 0));
    playerBoat = new PlayerBoat(0, 0);
    gameObjects.push_back(playerBoat);
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
    for (auto go : gameObjects) {
        camera->drawRect({go->x, go->y, go->w, go->h}, go->color);
    }
}

void World::onClick(float x, float y) {
    playerBoat->moveInLine(x, y, 60);
}
