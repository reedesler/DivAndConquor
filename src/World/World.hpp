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
#include "Game.hpp"
#include "Tilemap.h"
#include "Camera.hpp"
#include "PathRenderer.hpp"
#include "Attack.h"
#include "Sprite.hpp"
#ifdef __LINUX__
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#else
#include <SDL_mixer.h>
#include <SDL.h>
#endif

class PathRenderer;

class ShipObject;
class Sailor;
class Resource;
class EnemyAi;

enum State {
    invade,
    explore,
    flee,
    neutral,

};
class World
{
public:
  explicit World(Game* game, rect viewPort);
  void update();
  void draw(int pixelScale);
  void onClick(int button, int action, float xpos, float ypos);
  void onMouseMove(double xpos, double ypos);
  void setExplored(vec2 pos, float radius);
  void addShip();
  void addSettlement();
  void setResources();
  void setPirates();
    void setPirateSoldiers();
    void addSailor();
    GameObject * getClosestObjectOnLand(vec2 pos, bool playerControlled, bool landUnit);
  void centerCameraOn(GameObject &go);
  GameObject* getSelected() { return selectedObject; }
    bool checkWinCond();
  void fireOnClosestObject(GameObject * attacker, bool playerControlled, bool landUnit);

  // bool tooFar(GameObject * a, GameObject * b);

  Tilemap tilemap;
  Camera camera;
  long int w;
  bounds getWorldBounds();
  std::vector<GameObject *> selectedObjects;
  GameObject* selectedObject = nullptr; // primary selection
  GameObject *lock = nullptr;
  //Attack *attack;
  long int h;
    int navalStrength = 0;
    int pirateStrength = 0;
    int manPower = 0;
    int wealth = 0;
   // State state;
   State state = neutral;
   float coverage = 0;
    Mix_Chunk* fire = nullptr;
    bool firing = false;
    Mix_Music *background_music = nullptr;
    float settlementPoints = 0;


  Game* game;
    GameObject *getClosestObject(vec2 pos, bool playerControlled, bool landUnit);

  void removeGameObject(GameObject *obj);

    std::vector<GameObject *> gameObjects;
    std::vector<Attack *> bullets;
private:

  std::vector<GameObject *> toBeDeleted;
  Sprite selectOverlay;
  Sprite selectRing;
  Sprite hpBar;
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

  bool mouseDrag = false;
  vec2 mouseDragStart = {0,0};
  bounds mouseDragTempArea = {0,0,0,0}; // for display purposes during selection (before mouseup)
  long ticks = 0;
};

#endif //DIVCONQ_WORLD_H
