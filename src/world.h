//
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H

#include <vector>
#include "drawable.h"
#include "Camera.h"

class World : Drawable {
public:
    World(int w, int h, Camera *camera);

    ~World();

    void update() override;

    void draw(DrawContext *dc) override;

    Camera *camera;

private:
    std::vector<std::vector<int>> tilemap;
};


#endif //DIVCONQ_WORLD_H
