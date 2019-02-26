#ifndef DIVCONQ_SPRITE_H
#define DIVCONQ_SPRITE_H

#include "Common.hpp"
#include <map>
#include <array>

class Sprite : public Renderable
{
  Texture *texture;
  static std::map<const char *, Texture *> textures;

public:
  bool init(float width, float height, const char *textureName);
  void draw(const mat3 &projection, vec2 position, float rotation = 0, vec2 scale = {1.f, 1.f});
  float width, height;
  std::array<GLfloat,3 > tint;
  bool selected;
};

#endif //DIVCONQ_SPRITE_H