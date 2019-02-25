//
// Created by Dmitry on 2019-02-14.
//

#ifndef DIVCONQ_TILEMAP_H
#define DIVCONQ_TILEMAP_H


#include <vector>
#include <Common.hpp>

#define TILE_SIZE 100

// Single Vertex Buffer element for textured sprites (textured.vs.glsl)
struct TileVertex
{
    vec3 position;
    vec2 texcoord;
    bool explored;
};

class Tile {
public:
    unsigned char type;
    void setExplored(std::vector<TileVertex>& vertices);
    unsigned int vertexIndex;
private:
    bool explored = false;
};

class Tilemap: public Renderable {
public:
    Tilemap(Tile **map, unsigned int w, unsigned int h);
    static Tilemap LoadFromFile(std::string filepath);

    virtual ~Tilemap();

    unsigned int width;
    unsigned int height;
    void draw(const mat3 &projection);
    Tile getTile(float x, float y);
    void setExplored(vec2 pos, float radius);

private:
    Tile** map;
    Texture texture;
    std::vector<TileVertex> vertices;

};


#endif //DIVCONQ_TILEMAP_H
