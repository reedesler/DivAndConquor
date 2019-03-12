//
// Created by Dmitry on 2019-03-05.
//

#ifndef DIVCONQ_UIELEMENT_H
#define DIVCONQ_UIELEMENT_H


#include <Sprite.hpp>
#include <Ui/UiCallback.h>
class Game;

class UiElement {
    UiCallback::OnClickFunc callback;
public:
    explicit UiElement(Sprite &btn, vec2 location, UiCallback::OnClickFunc callback)
    : callback(callback), lastPressMs(0), pos(location), sprite(std::move(btn)), flashMs(200)
    {
    }
    long lastPressMs;
    vec2 pos;
    Sprite sprite;
    const int flashMs;
    void OnClick(Game *game, int action, double xpos, double ypos)
    {
        if (callback != nullptr) {
            callback(game, action, action, xpos, ypos);
        }
        this->lastPressMs = currentTimeMs();
    }

    virtual void Draw(const mat3 &projection){
        sprite.draw(projection, pos);
    }
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
        return hit;
    }

    void UpdateFlash(){
        float flash = 0.85f;
        if (lastPressMs > 0)
        {
            auto now = currentTimeMs();
            auto delta = flashMs - (now - lastPressMs);
            auto clamped = delta > 0 ? delta : 0;
            flash += 0.4f * (clamped / (float)flashMs);
        }
        sprite.tint = {flash, flash, flash};
    }
};


#endif //DIVCONQ_UIELEMENT_H
