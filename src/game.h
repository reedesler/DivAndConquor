//
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <SDL.h>
#include <vector>
#include "world.h"
#include "drawable.h"
#include "Camera.h"
#include "Tile.h"
#include "Pirate.h"

class Game
{
  public:
    explicit Game(DrawContext *dc);

    ~Game();

    void start();

  private:
    Camera camera;
    World world;
    DrawContext *dc;
    TileMap tilemap;
    std::vector<SDL_Texture *> mapTex;
    //Pirate pirate;
  public:
    void draw();

    void update();
};

#endif //DIVCONQ_GAME_H
