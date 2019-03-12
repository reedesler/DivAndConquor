//
// Created by Tomer Torgeman on 2019-03-07.
//

#ifndef DIVCONQ_BULLET_H
#define DIVCONQ_BULLET_H


#include "Common.hpp"

class Attack : public Renderable{

    static Texture attack_texture;


public:
    Attack(vec2);

    bool init();

    void travel(vec2);

    bool attackCondition(bool);

    void move();

    void draw(const mat3 &projection);

    void destroy();

    vec2 position;

    float width, height;

    vec2 texPiece = {1.f, 1.f};

    vec2 frame = {0.f,0.f};

    float rotation = 0;

    vec2 scale = {1.f, 1.f};

    vec2 target;
};


#endif //DIVCONQ_BULLET_H