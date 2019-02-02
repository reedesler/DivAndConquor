//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_BOAT_H
#define DIVCONQ_BOAT_H

#include "Unit.h"

class Boat : public Unit
{
  public:
    Boat(float x, float y);

    void move(float src_x, float src_y, float dest_x, float dest_y);
};

#endif //DIVCONQ_BOAT_H
