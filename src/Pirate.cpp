//
// Created by Tomer Torgeman on 2019-01-30.
//
#include <SDL_render.h>

#include "Pirate.h"
#include "draw_context.h"

static SDL_Surface * surface = SDL_LoadBMP("../assets/sprites/preview.bmp");
static SDL_Texture * texture;


Pirate::Pirate(int x, int y) {
    posX = x;
    posY = y;

}

//Pirate::~Pirate() = default;


void renderPirate(DrawContext *dc, Pirate * p){
    p = new Pirate(0,0);
    //SDL_FreeSurface(surface);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(dc->Renderer, surface);
    SDL_Rect destination;
    destination.x = p->posX;
    destination.y = p->posY;
    destination.w = 100;
    destination.h = 100;
    SDL_Rect src = {0,0,64,52};
    dc->drawTexture(texture, &src, &destination);
//    SDL_RenderCopy(dc->Renderer, texture, NULL, &destination);

}