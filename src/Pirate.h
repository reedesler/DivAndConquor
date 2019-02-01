//
// Created by Tomer Torgeman on 2019-01-30.
//

#ifndef DIVCONQ_PIRATE_H
#define DIVCONQ_PIRATE_H

#include <SDL_render.h>


class Pirate {

public:
    static SDL_Surface * surface;
    static SDL_Texture * texture;
    double posX;
    double posY;


    Pirate();

    void renderPirate(SDL_Renderer renderer);


private:

    //~Pirate();



};


#endif //DIVCONQ_PIRATE_H
