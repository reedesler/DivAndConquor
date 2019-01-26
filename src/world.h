//
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H

#include <vector>
class World {
public:
    World(int w, int h);
    ~World();

private:
    std::vector<std::vector<int>> tilemap;
};


#endif //DIVCONQ_WORLD_H
