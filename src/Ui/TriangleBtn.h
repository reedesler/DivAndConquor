//
// Created by Dmitry on 2019-03-05.
//

#ifndef DIVCONQ_PAUSEBTN_H
#define DIVCONQ_PAUSEBTN_H


#include "Button.hpp"

class TriangleBtn : public Button {

    virtual bool  InBounds(vec2 point)
    {
        float x0 = pos.x - sprite.width / 2.f;
        float x1 = pos.x + sprite.width / 2.f;
        float y0 = pos.y - sprite.height / 2.f;
        float y1 = pos.y + sprite.height / 2.f;
        bool hit = (point.x > x0 &&
                    point.x < x1 &&
                    point.y > y0 &&
                    point.y < y1);
        float x2 = (x0 + x1) / 2.f;
        float y2 = (y0 + y1) / 2.f;

        if (point.x <= x2)
            {
                float floor = y0 + sprite.height*(point.x - x0)/sprite.width;
                hit &= point.y > floor; 

            }
        return hit;
    }
    using Button::Button;
};


#endif //DIVCONQ_PAUSEBTN_H
