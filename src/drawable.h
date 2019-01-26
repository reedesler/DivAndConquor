//
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_DRAWABLE_H
#define DIVCONQ_DRAWABLE_H

#include <SDL.h>
#include "draw_context.h"

class Drawable {
public:
    virtual void draw(DrawContext* dc) = 0;
    virtual void update() = 0;
};

#endif //DIVCONQ_DRAWABLE_H
