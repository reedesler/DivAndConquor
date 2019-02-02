//
// Created by Dmitry on 2019-01-25.
//

#include "game.h"

#define UPDATE_INTERVAL_MS 1000/144

Game::Game(DrawContext *dc) : dc(dc), camera({0, 0, 1280, 800}, dc, &world), world(&tilemap, &camera) {
}

void Game::start() {
    SDL_Init(SDL_INIT_EVERYTHING);

    //map loading
    //done here because textures require a renderer(from dc). talk to Dima about how dc works
    buildMap(&tilemap, &mapTex, dc);


    auto lastUpdate = 0;
    SDL_Event event;
    while (true) {

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                return;
            } else {
                camera.handleInput(event);
            }
        }

        auto now = SDL_GetTicks();
        auto updateDebt = now - lastUpdate;
        // Call update one time for each interval we missed
        while (updateDebt >= UPDATE_INTERVAL_MS) {
            this->update();
            updateDebt -= UPDATE_INTERVAL_MS;
            lastUpdate = now;
        }

        this->draw();
    }

}

void Game::draw() {
    dc->clear({0, 0, 0, 255});
    this->world.draw(dc);
    dc->present();
}

Game::~Game() {}

void Game::update() {
    this->world.update();
}
