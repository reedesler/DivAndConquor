//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_PIRATEBOAT_H
#define DIVCONQ_PIRATEBOAT_H


#include "Boat.h"

class PirateBoat : public Boat {
public:
    PirateBoat(float x, float y);
    void update() override;

private:
    int counter;
    void setRandomDirection();
};


#endif //DIVCONQ_PIRATEBOAT_H
