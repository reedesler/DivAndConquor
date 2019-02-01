//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H

#include <SDL_pixels.h>
#include "stdio.h"

typedef struct Float_Point
{
    float x, y;
} Float_Point;

class GameObject {
public:
    GameObject(float x, float y);
    virtual void update();
    float w, h;
    float x, y;
    float velX, velY;
    SDL_Color color;

    void moveInLine(float x, float y, int speed);
private:
    Float_Point moveStart;
    Float_Point moveEnd;
    int moveTimer;
    int moveSpeed;
};


#endif //DIVCONQ_GAMEOBJECT_H
