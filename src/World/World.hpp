#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H
#ifndef DIVCONQ_WORLD_H_DEFINED
#define DIVCONQ_WORLD_H_DEFINED
    class World;
    #include "GameObject.hpp"
#endif


#include <vector>
#include "GameObject.hpp"
#include "Tilemap.h"
#include "Camera.hpp"
#include "Pirate.h"


class World {
public:
    explicit World(rect viewPort);
    void update(float);
    void draw(int pixelScale);
    void onClick(int button, int action, float xpos, float ypos);
    void setExplored(vec2 pos, float radius);
    void onClick2(int button, int action, float xpos, float ypos);
    Camera camera;
    Pirate pirate;

private:
    void on_key(int, int key, int, int action);
    void on_key2(int, int key, int scancode, int action);

        private:
    std::vector<GameObject *> gameObjects;
    Tilemap tilemap;

    GameObject* selectedObject = nullptr;
     Pirate * selected = nullptr;
    rect viewPort;



};


#endif //DIVCONQ_WORLD_H
