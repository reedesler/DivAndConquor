//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H

#include "stdio.h"


class GameObject {
public:
    GameObject(float x, float y);
    virtual void update();
private:
    float x, y;
    float velX, velY;
};


#endif //DIVCONQ_GAMEOBJECT_H
