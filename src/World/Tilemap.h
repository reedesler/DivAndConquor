//
// Created by Dmitry on 2019-02-14.
//

#ifndef DIVCONQ_TILEMAP_H
#define DIVCONQ_TILEMAP_H


#include <vector>
#include <Common.hpp>
#include <Sprite.hpp>

struct Tile {
    Tile();
    Tile(float x, float y, unsigned int type);
    float x, y;
    Sprite sprite;
    void draw(const mat3 &projection);
    unsigned int type;
};

class Tilemap {
public:
    Tilemap(std::string filepath);

    virtual ~Tilemap();

    unsigned int Width;
    unsigned int Height;
    void draw(const mat3 &projection);

private:
    Tile** map;
};


#endif //DIVCONQ_TILEMAP_H
