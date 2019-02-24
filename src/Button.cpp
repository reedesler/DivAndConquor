#include "Button.hpp"
#define BUTTON_FLASH_MS 200

Button::Button(Sprite &btn, vec2 location, Button::OnClickFunc callback) : callback(callback), lastPressMs(0), sprite(std::move(btn)), pos(location)
{
}

void Button::OnClick(int action, double xpos, double ypos){
    callback(-1, action, xpos, ypos);
    this->lastPressMs = currentTimeMs();
}

void Button::Draw(const mat3& projection) {
    float flash = 0.8f;
    if (lastPressMs > 0) {
        auto now = currentTimeMs() ;
        auto delta = BUTTON_FLASH_MS - (now - lastPressMs);
        auto clamped = delta > 0 ? delta : 0;
        flash  += 0.3f*(clamped / (float)BUTTON_FLASH_MS);
    }
    sprite.tint = {flash, flash, flash};
    sprite.draw(projection,pos);
}
bool Button::InBounds(vec2 point){
    float x0 = pos.x - sprite.width/2.f;
    float x1 = pos.x + sprite.width/2.f;
    // this is kinda strange:
    float y0 = pos.y - sprite.height ;
    float y1 = pos.y;
    bool hit = (point.x > x0 &&
                point.x < x1 &&
                point.y > y0 &&
                point.y < y1);
    return hit;
}

Button::~Button()
{
    
}