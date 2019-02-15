#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H

#include <vector>
#include "GameObject.hpp"

class World
{
  public:
    World();
    void update();
    void draw(const mat3 &projection);
    void moveCamera(vec2 dir);

  private:
    std::vector<GameObject *> gameObjects;
    vec2 cameraPos;
    vec2 cameraVel;
};

#endif //DIVCONQ_WORLD_H
