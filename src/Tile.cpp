//
// Created by Vova on 2019-01-31.
//

#include "Tile.h"

Tile::Tile(int x, int y, int type, SDL_Texture *texture)
{
    mbox.x = x;
    mbox.y = y;
    tType = type;
    tTexture = texture;
    mbox.h = TILE_SIDE;
    mbox.w = TILE_SIDE;
    tVisible = 1;
}

Tile::~Tile() = default;

//getters
int Tile::getType()
{
    return this->tType;
}

int Tile::isVisible()
{
    return this->tVisible;
}

SDL_Texture *Tile::getTex()
{
    return this->tTexture;
}

SDL_Rect *Tile::getBox()
{
    return &this->mbox;
}

//loading assets for the map.
//here until we implement some asset management

void buildMap(std::vector<std::vector<Tile *>> *map, std::vector<SDL_Texture *> *maptex, DrawContext *dc)
{

    //creating textures
    //should be improved
    SDL_Surface *loadedSurface = SDL_LoadBMP("../assets/mapgen/water.bmp");
    maptex->push_back(SDL_CreateTextureFromSurface(dc->Renderer, loadedSurface));
    free(loadedSurface);
    loadedSurface = SDL_LoadBMP("../assets/mapgen/sand.bmp");
    maptex->push_back(SDL_CreateTextureFromSurface(dc->Renderer, loadedSurface));
    free(loadedSurface);
    loadedSurface = SDL_LoadBMP("../assets/mapgen/grass.bmp");
    maptex->push_back(SDL_CreateTextureFromSurface(dc->Renderer, loadedSurface));
    free(loadedSurface);

    //loading map txt
    std::ifstream mapFile("../assets/mapgen/map1test.txt");

    //initializing tiles
    int type;
    for (int i = 0; i < TOTAL_SIDE; i++)
    {
        std::vector<Tile *> tmp;
        for (int j = 0; j < TOTAL_SIDE; j++)
        {
            type = mapFile.get() - 48;
            if (type == 3)
                type = 2;
            tmp.push_back(new Tile(j * TILE_SIDE, i * TILE_SIDE, type, (*maptex)[type]));
        }
        mapFile.get();
        map->push_back(tmp);
    }
}

bool Tile::reveal(TileLocation center)
{
    const int RADIUS = 3;
    for (int i = -RADIUS; i < RADIUS; i++)
    {
        for (int j = -RADIUS; j < RADIUS; j++)
        {
            this->tVisible = true;
        }
    }
    return true;
}