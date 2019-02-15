#include <utility>

//
// Created by Dmitry on 2019-02-14.
//

#include "Tilemap.h"
#include <string>
#include <iostream>
#include <fstream>


#define TILE_SIZE 100
#define TILE_SRC_SIZE 32

void Tilemap::draw(const mat3 &projection)
{
    for (int x = 0; x < Width; ++x)
        for (int y = 0; y < Height; ++y)
        {
            Tile t = map[y][x];
            t.draw(projection);
        }
}
Tilemap::~Tilemap() {
    for(int i = 0; i < Width; ++i) {
        delete [] map[i];
    }
    delete [] map;
}


Tilemap::Tilemap(std::string filepath) {
    std::ifstream infile;
    infile.open(filepath);
    if (!infile) {
        std::cerr << "Failed to load map file " << filepath << std::endl;
        exit(1);
    }
    std::string line;
    std::vector<std::vector<unsigned int>> temp;

    while( std::getline(infile, line)) {
        std::vector<unsigned int> row;
        for(char& c : line) {
            row.push_back(c-'0');
        }
        temp.push_back(row);
    }
    unsigned long w = temp[0].size();
    unsigned long h = temp.size();
    auto map = new Tile*[h];
    for (unsigned int x = 0; x < h; ++x) {
        map[x] = new Tile[w];
        for (unsigned int y = 0; y < w; ++y){
            map[x][y] = Tile(y * TILE_SIZE, x * TILE_SIZE, temp[x][y]); //transpose here, since we read it row-by-row
        }
    }
    this->map = map;
    this->Width = w;
    this->Height = h;
}

Tile::Tile(float x, float y, unsigned int type): x(x), y(y), type(type) {
    const char* path;
    switch (type) {
        default:
        case 0: path = textures_path("water.bmp"); break;
        case 1: path = textures_path("sand.bmp"); break;
        case 2: path = textures_path("grass.bmp"); break;
    }
    sprite.init(TILE_SIZE, TILE_SIZE, path);
}

void Tile::draw(const mat3 &projection) {
    sprite.draw(projection, {x, y});
}

Tile::Tile() {
}
