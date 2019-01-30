#include <iostream>
#include <SDL.h>
#include "game.h"

#define SDL_MAIN_HANDLED

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;

int main(int argc, char *argv[]) {


    std::cout << "Hello, World!" << std::endl;
    //The window we'll be rendering to
    SDL_Window *window = nullptr;


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("Divide and Conquer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {

            auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            auto drawContext = DrawContext(renderer);

            Game *game = new Game();
            game->Start(&drawContext);

        }
    }
    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}