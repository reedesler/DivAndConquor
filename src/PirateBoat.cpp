//
// Created by Reed on 2019-01-30.
//

#include <cstdlib>
#include "PirateBoat.h"

PirateBoat::PirateBoat(float x, float y) : Boat(x, y) {
    counter = 0;
    setRandomDirection();
}

void PirateBoat::update() {
    GameObject::update();
    counter++;
    if (counter > 120) {
        counter = 0;
        setRandomDirection();
    }
}

void PirateBoat::setRandomDirection() {
    double r = (double) rand() / RAND_MAX;
    printf("%lf\n", r);
}
