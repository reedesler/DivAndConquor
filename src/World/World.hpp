#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H
#ifndef DIVCONQ_WORLD_H_DEFINED
#define DIVCONQ_WORLD_H_DEFINED
class World;
#include "GameObject.hpp"
#endif

#include <vector>
#include <unordered_set>
#include "GameObject.hpp"
#include "Tilemap.h"
#include "Camera.hpp"
#include "Pirate.h"
#include "PathRenderer.hpp"

class PathRenderer;

class ShipObject;
class Pirate;

class World
{
  public:
    explicit World(rect viewPort);
    void update();
    void draw(int pixelScale);
    void onClick(int button, int action, float xpos, float ypos);
    void setExplored(vec2 pos, float radius);
    void addShip(ShipObject *ship);

    Camera camera;
    Tilemap tilemap;
    long int w;
    long int h;

  private:
    std::vector<GameObject *> gameObjects;

    int64_t balance;
    uint64_t sailors;
    std::unordered_set<ShipObject *> fleet;

    GameObject *selectedObject = nullptr;

    VisibleSet visibleTiles;
    PathRenderer* pathRenderer;
};

#endif //DIVCONQ_WORLD_H
