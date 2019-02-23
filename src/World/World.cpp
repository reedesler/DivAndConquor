#include "World.hpp"

World::World(rect viewPort) : tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt"))), camera(Camera(viewPort)) {
    gameObjects.push_back(new GameObject());
}

void World::update() {
    camera.update(tilemap.width, tilemap.height, TILE_SIZE);
}

void World::draw(int pixelScale) {
    mat3 projection = camera.getProjection(pixelScale);
    tilemap.draw(projection);
    for (auto o : gameObjects) {
        o->draw(projection);
    }
}
