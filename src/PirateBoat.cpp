//
// Created by Reed on 2019-01-30.
//

#include <cstdlib>
#include <math.h>
#include "PirateBoat.h"

PirateBoat::PirateBoat(float x, float y) : Boat(x, y) {
    counter = 0;
    setRandomDirection();
    w = 50;
    h = 20;
    color = {0, 0, 255, 255};
}

void PirateBoat::update() {
    Boat::update();
    counter++;
    if (counter > 120) {
        counter = 0;
        setRandomDirection();
    }
}

void PirateBoat::setRandomDirection() {
    double r = (double) rand() / RAND_MAX;
    double angle = r * 2 * M_PI;
    velX = static_cast<float>(cos(angle) * 5);
    velY = static_cast<float>(sin(angle) * 5);
}
