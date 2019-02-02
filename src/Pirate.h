//
// Created by Tomer Torgeman on 2019-01-30.
//

#ifndef DIVCONQ_PIRATE_H
#define DIVCONQ_PIRATE_H

#include <SDL_render.h>
#include "draw_context.h"


class Pirate {

public:
    static SDL_Surface * surface;
    static SDL_Texture * texture;
    int posX;
    int posY;


    Pirate(int, int);



private:

    //~Pirate();



};

void renderPirate(DrawContext *dc, Pirate *p);

#endif //DIVCONQ_PIRATE_H
