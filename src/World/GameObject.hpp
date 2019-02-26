#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H
#ifndef DIVCONQ_GAMEOBJECT_H_DEFINED
#define DIVCONQ_GAMEOBJECT_H_DEFINED
class GameObject;
#include "World.hpp"
#endif

#include "Sprite.hpp"
#include "math.h"
#include "Pathfinder.hpp"

class GameObject
{
  public:
    GameObject(World* world);
    void draw(const mat3 &projection);
    virtual void update();
    bounds getBounds();
    virtual void move(vec2 pos);
    void setSelected();
    bool onTerrain(vec2 loc, int type);
    Path path;

  protected:
    Sprite sprite;

    float w, h;
    vec2 position;  // Window coordinates
    vec2 scale;     // 1.f in each dimension. 1.f is as big as the associated texture
    float rotation; // in radians

    World* world;

    Pathfinder* pathfinder;
};

class ShipObject : public GameObject
{
public:
  ShipObject(World *world, vec2 loc);
  void travel(vec2 dir);
  void update();
  void move(vec2 pos);
  //void setDestination(vec2 dst);
  //void setVelocity(float vel);

private:
  float velocity;
  vec2 destination;

  //uint16_t gold;
  //uint16_t timber;
  //uint16_t iron;
};

#endif //DIVCONQ_GAMEOBJECT_H
