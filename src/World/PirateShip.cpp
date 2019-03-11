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
    pathfinder = new Pathfinder(world, landUnit, true);
}

void PirateShip::update() {
    GameObject::update();
    if (ticks % 60 == 0) {
        GameObject* o = world->getClosestObject(position, true, false);
        if (o) {
            vec2 targetPos = o->getPosition();
            TilePos start = Tilemap::getTilePos(position.x, position.y);
            TilePos goal = Tilemap::getTilePos(targetPos.x, targetPos.y);
            pathfinder->init(start.x, start.y, goal.x, goal.y);
            pathfinder->replan();
            path = pathfinder->getPath();
        }
    }


    if (!path.path.empty()) {
        auto next = std::next(path.path.begin());
        if (next == path.path.end()) return;
        float destX = next->x * TILE_SIZE;
        float destY = next->y * TILE_SIZE;
        if (abs(position.x - destX) <= SHIP_VELOCITY && abs(position.y - destY) <= SHIP_VELOCITY) {
            pathfinder->updateStart(next->x, next->y);
            pathfinder->replan();
            path = pathfinder->getPath();
        } else {
            travel({destX, destY});
        }
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
        position = newPos;
    }
}