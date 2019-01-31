//
// Created by Reed on 2019-01-30.
//

#include "GameObject.h"

GameObject::GameObject(float x, float y) : x(x), y(y) {
    velX = 0;
    velY = 0;
}

void GameObject::update() {
    x += velX;
    y += velY;
}
