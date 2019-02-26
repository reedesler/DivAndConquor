//
// Created by Tomer Torgeman on 2019-02-20.
//

#ifndef DIVCONQ_PIRATE_H
#define DIVCONQ_PIRATE_H


#include "Sprite.hpp"
#include "Common.hpp"

class Pirate : public Renderable {
    static Texture pirate_texture;

public:
    //Pirate();
    // Creates all the associated render resources and default transform
    bool init();

    // Releases all the associated resources
    void destroy();

    // Update turtle due to current
    // ms represents the number of milliseconds elapsed from the previous update() call
    void update(float ms);


    void updateFrame(float ms);

    void move(vec2 off);

    // Renders the salmon
    // projection is the 2D orthographic projection matrix
    void draw(const mat3 &projection);

    // Returns the current turtle position
    vec2 get_position() const;

    // Sets the new turtle position
    void set_position(vec2 position);

    // Returns the turtle' bounding box for collision detection, called by collides_with()
    vec2 get_bounding_box() const;

    bounds getBounds();
    void moveToPos(vec2 pos);
    void movement(vec2 pos);

private:

    vec2 p_scale; // 1.f in each dimension. 1.f is as big as the associated texture
    float p_rotation; // in radians

public:
    vec2 p_position; // Window coordinates
    float w;
    float h;
    bool moveUp;
    bool moveDown;
    bool moveLeft;
    bool moveRight;

};


#endif //DIVCONQ_PIRATE_H

