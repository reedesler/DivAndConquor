#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H
#ifndef DIVCONQ_GAMEOBJECT_H_DEFINED
    #define DIVCONQ_GAMEOBJECT_H_DEFINED
    class GameObject;
    #include "World.hpp"
#endif

#include "Sprite.hpp"

class GameObject
{
  public:
    GameObject(World* world);
    void draw(const mat3 &projection);
    void update();
    bounds getBounds();
    void move(vec2 pos);

  private:
    Sprite sprite;

    float w, h;

    vec2 position;  // Window coordinates
    vec2 scale;     // 1.f in each dimension. 1.f is as big as the associated texture
    float rotation; // in radians

    World* world;
};

#endif //DIVCONQ_GAMEOBJECT_H
