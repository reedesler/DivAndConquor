//
// Created by Vova on 2019-01-31.
//

#ifndef DIVCONQ_TILE_H
#define DIVCONQ_TILE_H

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include "draw_context.h"

//Tile constants
const int TILE_SIDE = 100;
const int TOTAL_SIDE = 500;
const int TOTAL_TILE_TYPES = 3;
const int TEX_LENGTH = 100;

typedef struct
{
    uint32_t x;
    uint32_t y;
} TileLocation;

class Tile
{
  public:
    Tile(int x, int y, int type, SDL_Texture *texture);

    int getType();
    SDL_Rect *getBox();
    SDL_Texture *getTex();
    int isVisible();

    // should be called by the ship or settler which has visited the location
    bool reveal(TileLocation center);

  private:
    int tType;

    int tVisible;

    SDL_Rect mbox;

    SDL_Texture *tTexture;

    ~Tile();
};

typedef std::vector<std::vector<Tile *>> TileMap;

void buildMap(std::vector<std::vector<Tile *>> *map, std::vector<SDL_Texture *> *maptex, DrawContext *dc);
#endif //DIVCONQ_TILE_H
