#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H

#include "Sprite.hpp"

class GameObject
{
  public:
    GameObject();
    void draw(const mat3 &projection);
    bounds getBounds();
    void move(vec2 pos);

  private:
    Sprite sprite;

    float w, h;

    vec2 position;  // Window coordinates
    vec2 scale;     // 1.f in each dimension. 1.f is as big as the associated texture
    float rotation; // in radians
};

#endif //DIVCONQ_GAMEOBJECT_H
