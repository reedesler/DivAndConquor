#include <iostream>
#include <SDL.h>
#include "game.h"

#define SDL_MAIN_HANDLED

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;

int main(int argc, char *argv[]) {

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("Divide and Conquer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            auto drawContext = DrawContext(renderer);

            Game *game = new Game();
            game->start(&drawContext);

        }
    }

    //Destroy window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}