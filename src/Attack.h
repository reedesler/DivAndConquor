//
// Created by Tomer Torgeman on 2019-03-07.
//

#ifndef DIVCONQ_BULLET_H
#define DIVCONQ_BULLET_H

#include "Common.hpp"

class GameObject;

class Attack : public Renderable
{

  static Texture attack_texture;

public:
  Attack(vec2, vec2, GameObject* shooter);
    ~Attack();


    bool init();

  void travel();

  GameObject* shooter;

    bounds getBounds();

  bool attackCondition(bool);

  void move();

  void draw(const mat3 &projection);

  void destroy();

  bool collidesWith(vec2 circlePosition, float radius, vec2 rectLeftTop, vec2 rectRightBottom);

  vec2 position;

  float width, height;

  vec2 texPiece = {1.f, 1.f};

  vec2 frame = {0.f, 0.f};

  float rotation = 0;

  vec2 scale = {1.f, 1.f};

  vec2 direction;

  int ticks = 0;
};

#endif //DIVCONQ_BULLET_H
