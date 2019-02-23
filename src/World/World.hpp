#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H


#include <vector>
#include "GameObject.hpp"
#include "Tilemap.h"
#include "Camera.hpp"

class World {
public:
    explicit World(rect viewPort);
    void update();
    void draw(int pixelScale);
    Camera camera;

private:
    std::vector<GameObject *> gameObjects;
    Tilemap tilemap;
};


#endif //DIVCONQ_WORLD_H
