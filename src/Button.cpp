//
// Created by David Ma on 2019-01-30.
//

#include "Button.h"

Button::Button(int x, int y, int w, int h, std::string text)
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

    displayText = text;

    // Set the default sprite
    // clip = &clips[CLIP_MOUSEOUT];
}

void Button::handle_events(SDL_Event event)
{
    //The mouse offsets
    int x = 0, y = 0;

    //If the mouse moved
    if (event.type == SDL_MOUSEMOTION)
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if ((x > box.x) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
        {
            //Set the button sprite
            // clip = &clips[CLIP_MOUSEOVER];
        }
        //If not
        else
        {
            //Set the button sprite
            // clip = &clips[CLIP_MOUSEOUT];
        }
    }
}