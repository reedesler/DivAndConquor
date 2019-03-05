//
// Created by Dmitry on 2019-02-14.
//

#ifndef DIVCONQ_TILEMAP_H
#define DIVCONQ_TILEMAP_H


#include <vector>
#include <unordered_set>
#include <Common.hpp>

#define TILE_SIZE 100
#define EXPLORED_BUT_NOT_VISIBLE 0.7f

// Single Vertex Buffer element for textured sprites (textured.vs.glsl)
struct TileVertex
{
    vec3 position;
    vec2 texcoord;
    float explored;
    GLint tileid;
    TransitionState tranState;
    float tranStartTime;
};


struct TilePos {
    int x, y;
    bool operator == (const TilePos &s2) const {
        return ((x == s2.x) && (y == s2.y));
    }
};

class TilePosHash {
public:
    size_t operator()(const TilePos &s) const {
        return s.x + 34245*s.y;
    }
};

typedef std::unordered_set<TilePos, TilePosHash> VisibleSet;

class Tile {
public:
    unsigned char type;
    void setExplored(std::vector<TileVertex>& vertices);
    void setVisible(std::vector<TileVertex>& vertices, bool visible);
    unsigned int vertexIndex;
    bool explored = false;
    bool visible = false;
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
    static TilePos getTilePos(float x, float y);
    void setExplored(VisibleSet& tiles);
    void clearVisible(VisibleSet& tiles);
    Tile** map;

private:
    Texture texture;
    std::vector<TileVertex> vertices;

};


#endif //DIVCONQ_TILEMAP_H
