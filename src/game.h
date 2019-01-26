//
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <SDL.h>
#include <vector>
#include "world.h"
#include "drawable.h"

class Game: public Drawable {
public:
    Game();
    ~Game();
    void Start(DrawContext* dc);

private:

    World world;
public:
    void draw(DrawContext *dc) override;

    void update() override;

};


#endif //DIVCONQ_GAME_H
