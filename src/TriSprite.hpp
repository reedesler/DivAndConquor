#ifndef DIVCONQ_TriSprite_H
#define DIVCONQ_TriSprite_H

#include "Common.hpp"
#include <map>
#include <array>
#include "Sprite.hpp"

class TriSprite : public Sprite
{
public:
  virtual bool init(float width, float height, const char *textureName, vec2 texPiece = {1.f,1.f}) override;
  virtual void draw(const mat3 &projection, vec2 position, float rotation = 0, vec2 scale = {1.f, 1.f}) override;
};

#endif //DIVCONQ_TriSprite_H
