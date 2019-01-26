//
// Created by Dmitry on 2019-01-25.
//

#include "game.h"
#include <math.h>
#include <SDL.h>
#include <iostream>

#define UPDATE_INTERVAL_MS 1000/144

Game::Game():world(500,500) {

}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn" // so it doesn't complain about inf loop
void Game::Start (DrawContext* dc)  {
    SDL_Init(SDL_INIT_EVERYTHING);

    auto lastUpdate = 0;
    SDL_Event event;
    while (true) {

        // gotta handle OS events so window doesn't freeeze
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }
        auto now = SDL_GetTicks();
        auto updateDebt =now - lastUpdate;
        // Call update one time for each interval we missed
        while(updateDebt >= UPDATE_INTERVAL_MS){
            this->update();
            updateDebt -= UPDATE_INTERVAL_MS;
            lastUpdate = now;
        }

        this->draw(dc);
    }

}
#pragma clang diagnostic pop
#pragma clang diagnostic pop

// test to make sure periodic update is smooth
double t = 0.;

void Game::draw(DrawContext *dc) {
    auto c = cos(t);
    auto s = sin(t);
    dc->clear({0,0,0,255});
    dc->drawLine(255,255,255 + (int)(c*255.f),255+(int)(s*255.f),{(uint8_t )(128+c*127.f),(uint8_t )(128+s*127.f),(uint8_t )(128-c*127.f),255});
    dc ->present();

}

Game::~Game() {

}

void Game::update() {
    t = SDL_GetTicks()/1000.f;
}
