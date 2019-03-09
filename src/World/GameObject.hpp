#ifndef DIVCONQ_GAMEOBJECT_H
#define DIVCONQ_GAMEOBJECT_H
#ifndef DIVCONQ_GAMEOBJECT_H_DEFINED
#define DIVCONQ_GAMEOBJECT_H_DEFINED

class GameObject;

#include "World.hpp"

#endif

#include "Sprite.hpp"
#include "math.h"
#include "Pathfinder.hpp"

class GameObject {
public:
    GameObject(World *world, vec2 loc);

    virtual void draw(const mat3 &projection);

    virtual void update();

    bounds getBounds();

    virtual void move(vec2 pos);

    virtual void setSelected();

    vec2 getPosition() {return position;};
    bool onTerrain(vec2 loc, int type);

    Pathfinder *pathfinder = nullptr;
    Path path;
    bool landUnit;
    Sprite& getSprite() {return sprite;};

    bool playerControlled = true;

protected:
    Sprite sprite;

    float w, h;
    vec2 position;  // Window coordinates
    vec2 scale;     // 1.f in each dimension. 1.f is as big as the associated texture
    float rotation; // in radians

    World *world;

};

class ShipObject : public GameObject {
public:
    ShipObject(World *world, vec2 loc);

    void travel(vec2 dir);

    void update();

    void move(vec2 pos);
    //void setDestination(vec2 dst);
    //void setVelocity(float vel);

private:

    //uint16_t gold;
    //uint16_t timber;
    //uint16_t iron;
};

class PirateShip : public GameObject {
public:
    PirateShip(World *world, vec2 loc);

    void travel(vec2 dir);

    void update();
};

class Sailor : public GameObject{
public:
    Sailor(World *world, vec2 pos);
    void travel(vec2 dir);
    void update();
    void renderDirection(vec2 dir);
    void move(vec2 pos);

    float frameNo;

    int r = std::rand();
};

class SettlementObject : public GameObject {
public:
    SettlementObject(World *world, vec2 loc);

    void update();

    void move(vec2 pos);

    vec3 getResources();
    //void setDestination(vec2 dst);
    //void setVelocity(float vel);

private:
    uint16_t gold;
    uint16_t timber;
    uint16_t iron;
};

class Loot: public GameObject{
public:
    Loot(World *world, vec2 loc, uint16_t type, uint16_t size);

    void collect(GameObject *obj);
private:
    uint16_t loot_type;
    uint16_t resource;
};

class Pirate : public GameObject, public Renderable {

    static Texture pirate_texture;

public:
    bool init();

    // Creates all the associated render resources and default transform
    Pirate(World *world, vec2 pos);

    // Releases all the associated resources
    //void destroy();

    // Update turtle due to current
    // ms represents the number of milliseconds elapsed from the previous update() call
    void update(float ms);



    void updateFrame(float ms);

    void move(vec2 off);

    // Renders the salmon
    // projection is the 2D orthographic projection matrix
    void draw(const mat3 &projection);

    void setSelected();

    // Returns the current turtle position
    vec2 get_position() const;

    // Sets the new turtle position
    void set_position(vec2 position);

    // Returns the turtle' bounding box for collision detection, called by collides_with()
    vec2 get_bounding_box() const;

    // bounds getBounds();
    void moveToPos(vec2 pos);

    void movement(vec2 pos);

public:
    //vec2 p_position; // Window coordinates
    //float w;
    //float h;
    bool moveUp = true;
    bool moveDown;
    bool moveLeft;
    bool moveRight;
    bool selected;
    std::array<GLfloat, 3> tint;
};


#endif //DIVCONQ_GAMEOBJECT_H
