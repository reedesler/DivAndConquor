//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_BOAT_H
#define DIVCONQ_BOAT_H

#include "Unit.h"
#include "Tile.h"

#include <vector>

typedef struct
{
    float x;
    float y;
} Point;

class Boat : public Unit
{
  public:
    Boat(float x, float y);

    Boat(TileLocation src, TileLocation dest);

    void move(TileLocation src, TileLocation dest);

  private:
    bool sailing;
    TileLocation src;
    TileLocation dest;
    std::vector<TileLocation> tilesToBeVisited;
    std::vector<Point> pointsToBeTraversed;
};

#endif //DIVCONQ_BOAT_H
