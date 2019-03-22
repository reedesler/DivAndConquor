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
#include "Attack.h"

class GameObject {
public:
    GameObject(World *world, vec2 loc);
    virtual ~GameObject();

    virtual void draw(const mat3 &projection);

    virtual void update();

    bounds getBounds();

    void fire(vec2, vec2);

    bool tooFar(GameObject * a, GameObject * b);

    virtual void move(vec2 pos);

    virtual void setSelected();

    virtual void lockOn();

    vec2 getPosition() {return position;};
    bool onTerrain(vec2 loc, int type);

    Pathfinder * pathfinder = nullptr;

    GameObject(Pathfinder *pathfinder);

    Attack * attack = nullptr;
    Path path;
    bool landUnit;
    Sprite& getSprite() {return sprite;};
    bool fight = false;
    bool init = false;
    bool canShoot;
    bool playerControlled = true;
    //int health = 100;

    virtual void collide(GameObject* obj);

    float health;
    float maxHealth;

protected:
    Sprite sprite;

    float w, h;
    vec2 scale;     // 1.f in each dimension. 1.f is as big as the associated texture
    float rotation; // in radians
    World *world;

    long ticks = 0;

    void addForce(vec2 f);

    void destroy();

    vec2 position;
    vec2 velocity;
    vec2 forces;

};

class SettlementObject : public GameObject {
public:
    SettlementObject(World *world, vec2 loc);

    void update();

    void move(vec2 pos);

    vec3 getResources();

    void updateResources(uint16_t type, int amount);

private:
    int gold;
    int timber;
    int iron;
};

class ShipObject : public GameObject {
public:
    ShipObject(World *world, vec2 loc, SettlementObject *settlement);

    void travel(vec2 dir);

    void update();

    void move(vec2 pos);

    void collide(GameObject* obj);

    SettlementObject* settlement;

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
    void collide(GameObject* obj);
};

class Sailor : public GameObject{
public:
    Sailor(World *world, vec2 pos, SettlementObject *settlement);
    void travel(vec2 dir);
    void update();
    void renderDirection(vec2 dir);
    void move(vec2 pos);


    float frameNo;
    int r = std::rand();
    SettlementObject *settlement;
};

class Resource: public GameObject{
public:
    Resource(World *world, vec2 loc, uint16_t type, int size);

    bool collect(Sailor *obj);
private:
    uint16_t loot_type;
    int resource;
};

class Pirate : public GameObject {

    static Texture pirate_texture;

public:
    bool init();

    // Creates all the associated render resources and default transform
    Pirate(World *world, vec2 pos);

    // Releases all the associated resources
    //void destroy();

    // Update turtle due to current
    // ms represents the number of milliseconds elapsed from the previous update() call
    void update();

    void renderDirection(vec2);

    void travel(vec2);

    void updateFrame(float ms);

    void move(vec2 off);

    // Renders the salmon
    // projection is the 2D orthographic projection matrix
   // void draw(const mat3 &projection);

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
    float frameNo;
    int r = std::rand();

    bool moveUp = true;
    bool moveDown;
    bool moveLeft;
    bool moveRight;
    bool selected;
    bool enemy;
    std::array<GLfloat, 3> tint;
};



#endif //DIVCONQ_GAMEOBJECT_H
