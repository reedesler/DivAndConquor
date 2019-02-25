#include "World.hpp"

World::World(rect viewPort) : camera(Camera(viewPort)),
                              tilemap(Tilemap::LoadFromFile(maps_path("map_horizontal.txt"))) {
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

void World::onClick(int button, int action, float xpos, float ypos) {
    if (action == GLFW_PRESS) {
        vec2 worldCoords = camera.viewToWorld({xpos, ypos});
        for (auto o : gameObjects) {
            bounds b = o->getBounds();
            if (inBounds(b, worldCoords)) {
                selectedObject = o;
                return;
            }
        }

        if (selectedObject != nullptr) {
            selectedObject->move(worldCoords);
        }
    }
}
