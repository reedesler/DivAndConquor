//
// Created by Reed on 2019-01-30.
//

#include "GameObject.h"

GameObject::GameObject(float x, float y) : x(x), y(y) {
    velX = 0;
    velY = 0;
    moveSpeed = 0;
    moveTimer = 1;
}

void GameObject::update() {
    if (moveTimer <= moveSpeed) {
        float t = (float) moveTimer / (float) moveSpeed;
        x = moveStart.x + (moveEnd.x - moveStart.x) * t;
        y = moveStart.y + (moveEnd.y - moveStart.y) * t;
        moveTimer++;
    } else {
        x += velX;
        y += velY;
    }
}

void GameObject::moveInLine(float x, float y, int speed) {
    moveTimer = 0;
    moveStart = {this->x, this->y};
    moveEnd = {x, y};
    moveSpeed = speed;
}
