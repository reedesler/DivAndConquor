//
// Created by Tomer Torgeman on 2019-01-30.
//

#include "Pirate.h"

static SDL_Surface * surface = IMG_Load("/Users/tomertorgeman/Desktop/Project/sailor_and_pirate-1.1/preview.png");
static SDL_Texture * texture;


Pirate::Pirate(double x, double y) {
    posX = x;
    posY = y;

}

//Pirate::~Pirate() = default;


void renderPirate(SDL_Renderer render){
    Pirate * p = new Pirate(0,0);
    SDL_FreeSurface(surface);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect destination;
    destination.x = 0;
    destination.y = 0;
    destination.w = 100;
    destination.w = 100;

    SD_RenderCopy(render, texture, NULL, &destination);

}