#include <utility>

//
// Created by Dmitry on 2019-02-14.
//

#include "Tilemap.h"
#include <string>
#include <iostream>
#include <fstream>


#define TILE_SIZE 64
#define TILE_SRC_SIZE 32
Tilemap LoadFromFile(std::string filepath) {
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
    unsigned int w = temp[0].size();
    unsigned int h = temp.size();
    auto map = new unsigned int*[w];
    for (unsigned int x = 0; x < w; ++x) {
        map[x] = new unsigned int[h];
        for (unsigned int y = 0; y < h; ++y){
            map[x][y] = temp[y][x]; //transpose here, since we read it row-by-row
        }
    }

    Tilemap t = Tilemap(map, w, h);
    return t;

}

void Tilemap::draw(const mat3 &projection)
{
    // TODO
    for (int x = 0; x < Width; ++x)
        for (int y = 0; y < Width; ++y)
        {
            unsigned int tilemap_n = map[x][y];
            // oh boy


        }


}
Tilemap::~Tilemap() {
    for(int i = 0; i < Width; ++i) {
        delete [] map[i];
    }
    delete [] map;
}


Tilemap::Tilemap(unsigned int** map, unsigned  int w, unsigned int h) : map(map),Width(w), Height(h) {
    // Load shared texture
    if (!texture.is_valid())
    {
        if (!texture.load_from_file(textures_path("tilemap.png")))
        {
            fprintf(stderr, "Failed to load map texture!");
            exit(1);
        }
    }

    // Loading shaders
    if(!effect.load_from_file(shader_path("textured.vs.glsl"), shader_path("textured.fs.glsl")))
    {

        fprintf(stderr, "Failed to load map shaders!");
        exit(1);
    }
}
