//
// Created by Dmitry on 2019-02-14.
//

#ifndef DIVCONQ_TILEMAP_H
#define DIVCONQ_TILEMAP_H


#include <vector>
#include <Common.hpp>

class Chunk {
    unsigned int** map;
    unsigned int width;
    unsigned int height;
};

class Tilemap: public Renderable {
public:
    Tilemap(unsigned int **map, unsigned int w, unsigned int h);
    static Tilemap LoadFromFile(std::string filepath);

    virtual ~Tilemap();

    unsigned int width;
    unsigned int height;
    void draw(const mat3 &projection);

private:
    unsigned int** map;
    Texture texture;

};


#endif //DIVCONQ_TILEMAP_H
