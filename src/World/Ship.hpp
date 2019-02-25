//
// Created by veshuga on 2019-02-24.
//

#ifndef DIVCONQ_SHIP_H
#define DIVCONQ_SHIP_H
#ifndef DIVCONQ_SHIP_H_DEFINED
    #define DIVCONQ_SHIP_H_DEFINED
    class Ship;
    #include "World.hpp"
#endif

#include "./../Sprite.hpp"

class Ship{
public:
    Ship(World *world, vec2 loc, vec2 size);
    void travel();
    void setDestination(vec2 dst);
    void setVelocity(float vel);
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
    float velocity;
    vec2 destination;
};



#endif //DIVCONQ_SHIP_H
