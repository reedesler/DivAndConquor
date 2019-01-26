//
// Created by Dmitry on 2019-01-25.
//

#include "world.h"
#include <vector>

World::World(int w, int h) {

    this->tilemap.resize(w, std::vector<int>(h, 0));
}

World::~World() {

}
