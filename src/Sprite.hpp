#ifndef DIVCONQ_SPRITE_H
#define DIVCONQ_SPRITE_H

#include "Common.hpp"

class Sprite : public Renderable
{
    Texture texture;

  public:
    bool init(float width, float height);
    void draw(const mat3 &projection, vec2 position, float rotation = 0, vec2 scale = {1.f, 1.f});
};

#endif //DIVCONQ_SPRITE_H
