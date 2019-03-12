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
#include "PathRenderer.hpp"

class PathRenderer;

class ShipObject;
class Sailor;
class Resource;

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
    void setResources();
    void addSailor(Sailor * sailor);
    void centerCameraOn(GameObject &go);
    GameObject* getSelected() { return selectedObject;}

    Tilemap tilemap;
    Camera camera;
    long int w;
    GameObject *selectedObject = nullptr;

    long int h;

    GameObject* getClosestObject(vec2 pos, bool playerControlled, bool landUnit);

    void removeGameObject(GameObject* obj);
private:

    std::vector<GameObject *> gameObjects;
    std::vector<GameObject *> toBeDeleted;
    int64_t balance;
    uint64_t sailors;

    std::vector<ShipObject *> fleet;
    std::vector<Sailor *> army;
    std::vector<Resource *> resources;

    VisibleSet visibleTiles;
    PathRenderer* pathRenderer;

    double prevMouseXpos, prevMouseYpos;
};

#endif //DIVCONQ_WORLD_H
