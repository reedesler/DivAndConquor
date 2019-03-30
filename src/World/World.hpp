#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H
#ifndef DIVCONQ_WORLD_H_DEFINED
#define DIVCONQ_WORLD_H_DEFINED
class World;
#include "GameObject.hpp"
#endif

#include "EnemyAi.h"
#include <vector>
#include <unordered_set>
#include "GameObject.hpp"
#include "Tilemap.h"
#include "Camera.hpp"
#include "PathRenderer.hpp"
#include "Attack.h"
class PathRenderer;

class ShipObject;
class Sailor;
class Resource;
class EnemyAi;

class World
{
public:
  explicit World(rect viewPort);
  void update();
  void draw(int pixelScale);
  void onClick(int button, int action, float xpos, float ypos);
  void onMouseMove(double xpos, double ypos);
  void setExplored(vec2 pos, float radius);
  void addShip();
  void addSettlement();
  void setResources();
  void setPirates();
  void addSailor();
  void centerCameraOn(GameObject &go);
  GameObject *getSelected() { return selectedObject; }

  void fireOnClosestObject(GameObject * attacker, bool playerControlled, bool landUnit);

  // bool tooFar(GameObject * a, GameObject * b);

  Tilemap tilemap;
  Camera camera;
  long int w;
  GameObject *selectedObject = nullptr;
  GameObject *lock = nullptr;
  //Attack *attack;
  long int h;
    int navalStrength = 0;
    int manPower = 0;
    int wealth = 0;

  GameObject *getClosestObject(vec2 pos, bool playerControlled, bool landUnit);

  void removeGameObject(GameObject *obj);

    std::vector<GameObject *> gameObjects;
    std::vector<Attack *> bullets;
private:

  std::vector<GameObject *> toBeDeleted;

    std::vector<Attack *> pastAttacks;
    int64_t balance;

  uint64_t sailors;
    std::vector<ShipObject *> fleet;
    std::vector<Sailor *> army;
    std::vector<Resource *> resources;

  VisibleSet visibleTiles;
  PathRenderer *pathRenderer;
  EnemyAi * ai;

  double prevMouseXpos, prevMouseYpos;

  long ticks = 0;
};

#endif //DIVCONQ_WORLD_H
