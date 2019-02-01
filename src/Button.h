//
// Created by David Ma on 2019-01-30.
//

#ifndef DIVCONQ_BUTTON_H
#define DIVCONQ_BUTTON_H

#include <string>

#include "SDL.h"

class Button
{
  private:
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    SDL_Rect *clip;

    std::string displayText;

  public:
    //Initialize the variables
    Button(int x, int y, int w, int h, std::string text);

    //Handles events and set the button's sprite region
    void handle_events(SDL_Event event);

    //Shows the button on the screen
    void show();
};

#endif //DIVCONQ_BUTTON_H