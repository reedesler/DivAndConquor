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
class Sailor;

class World
{
  public:
    explicit World(rect viewPort);
    void update();
    void draw(int pixelScale);
    void onClick(int button, int action, float xpos, float ypos);
    void onMouseMove(double xpos, double ypos);
    void setExplored(vec2 pos, float radius);
    void addShip(ShipObject *ship);
    void addSailor(Sailor * sailor);

    Tilemap tilemap;
    Camera camera;
    long int w;
    GameObject *selectedObject = nullptr;

    long int h;
private:

    std::vector<GameObject *> gameObjects;
    int64_t balance;
    uint64_t sailors;

    std::unordered_set<ShipObject *> fleet;

    VisibleSet visibleTiles;
    PathRenderer* pathRenderer;

    double prevMouseXpos, prevMouseYpos;
};

#endif //DIVCONQ_WORLD_H
