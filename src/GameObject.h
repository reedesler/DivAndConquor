//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H

#include <SDL_pixels.h>
#include "stdio.h"


class GameObject {
public:
    GameObject(float x, float y);
    virtual void update();
    float w, h;
    float x, y;
    float velX, velY;
    SDL_Color color;
};


#endif //DIVCONQ_GAMEOBJECT_H
