#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H
#ifndef DIVCONQ_WORLD_H_DEFINED
    #define DIVCONQ_WORLD_H_DEFINED
    class World;
    #include "GameObject.hpp"
#endif


#include <vector>
#include "Tilemap.h"
#include "Ship.hpp"
#include "Camera.hpp"

class World {
public:
    explicit World(rect viewPort);
    void update();
    void draw(int pixelScale);
    void onClick(int button, int action, float xpos, float ypos);
    Camera camera;
    void setExplored(vec2 pos, float radius);
private:
    std::vector<GameObject *> gameObjects;
    std::vector<Ship *> ships;
    Tilemap tilemap;

    GameObject* selectedObject = nullptr;
};


#endif //DIVCONQ_WORLD_H
