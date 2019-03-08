#include "GameObject.hpp"

#define SHIP_VELOCITY 4

PirateShip::PirateShip(World* world, vec2 loc) : GameObject(world, loc) {
    w = 100;
    h = 100;
    if (!sprite.init(w, h, textures_path("ship.png"), {0.5f, 1.f})) {
        printf("ERROR initializing sprite\n");
    }
    sprite.tint = {1.f, 0.5f, 0.5f};
    rotation = 0;
    scale = {1.f, 1.f};
    landUnit = false;
    playerControlled = false;
}

void PirateShip::update() {
    GameObject* o = world->getClosestObject(position, true, false);
    if (o) {
        travel(o->getPosition());
    }
}

void PirateShip::travel(vec2 destination) {
    vec2 dir = {destination.x - position.x, destination.y - position.y};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > SHIP_VELOCITY) {
        dir = {dir.x / length, dir.y / length};
        this->rotation = atan2(dir.y, dir.x);
        if (abs(rotation) > M_PI / 2) {
            this->sprite.state = 1;
            rotation = atan2(-dir.y, -dir.x);
        } else {
            this->sprite.state = 0;
        }

        vec2 newPos = {position.x + dir.x * SHIP_VELOCITY, position.y + dir.y * SHIP_VELOCITY};
        if (onTerrain(newPos, 0)) {
            position = newPos;
        }
    }
}