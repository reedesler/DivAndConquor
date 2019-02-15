#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H


#include <vector>
#include "GameObject.hpp"
#include "Tilemap.h"

class World {
public:
    World();
    void update();
    void draw(const mat3& projection);
    void moveCamera(vec2 dir, int i);

private:
    std::vector<GameObject *> gameObjects;
    vec2 cameraPos;
    vec2 cameraVel;
    float cameraZoomVel;
    float cameraZoom;
    Tilemap tilemap;
};


#endif //DIVCONQ_WORLD_H
