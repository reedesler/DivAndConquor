#include <iostream>
#include <SDL.h>
#include "game.h"
#include "Pirate.h"
#include <SDL_render.h>


#define SDL_MAIN_HANDLED

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1024;
Pirate * pirate;
static SDL_Surface * surface;
static SDL_Texture * texture;
int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
  //  surface = pirate->surface;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("Divide and Conquer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            int drawW, drawH;
            SDL_GetRendererOutputSize(renderer, &drawW, &drawH);
            int xScale = drawW / SCREEN_WIDTH;
            int yScale = drawH / SCREEN_HEIGHT;
            auto drawContext = DrawContext(renderer, xScale, yScale);


            //Pirate * p = new Pirate(0, 0);

//            SDL_FreeSurface(surface);
//            texture = SDL_CreateTextureFromSurface(renderer, surface);
//            SDL_Rect destination;
//            destination.x = 0;
//            destination.y = 0;
//            destination.w = 100;
//            destination.w = 100;

//            SDL_RenderCopy(renderer, texture, NULL, &destination);


            Game game = Game(&drawContext);
            game.start();

        }
    }

    //Destroy window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}