//
// Created by veshuga on 2019-02-24.
//

#include "GameObject.hpp"

#define SHIP_VELOCITY 2

ShipObject::ShipObject(World *world, vec2 loc, SettlementObject *settlement) : GameObject(world, loc) {
    w = 100;
    h = 100;
    if (!sprite.init(w, h, textures_path("ship.png"), {0.5f, 1.f})) {
        printf("ERROR initializing sprite\n");
    }
    rotation = 0;
    scale = {1.f, 1.f};
    landUnit = false;
    pathfinder = new Pathfinder(world, landUnit);
    health = maxHealth = 100;
    canShoot = true;
    this->settlement = settlement;
    settlement->updateResources(0, -500);
}

void ShipObject::move(vec2 pos) {
    vec2 position = getPosition();
    TilePos start = Tilemap::getTilePos(position.x, position.y);
    TilePos goal = Tilemap::getTilePos(pos.x, pos.y);
    pathfinder->init(start.x, start.y, goal.x, goal.y);
    pathfinder->replan();
    path = pathfinder->getPath();

}

void ShipObject::update() {

    GameObject::update();

    vec2 position = getPosition();
    if (attack){
        if(attack->attackCondition(fight)){
            fight = false;
        }
    }

    world->setExplored(position, 7 * TILE_SIZE);
    if (!path.path.empty()) {
        auto next = std::next(path.path.begin());
        if (next != path.path.end()) {
            float destX = next->x * TILE_SIZE;
            float destY = next->y * TILE_SIZE;
            if (abs(position.x - destX) <= SHIP_VELOCITY * 2 && abs(position.y - destY) <= SHIP_VELOCITY * 2) {
                pathfinder->updateStart(next->x, next->y);
                pathfinder->replan();
                path = pathfinder->getPath();
            } else {
                travel({destX, destY});
            }
        };
    }

    TilePos tilePos = Tilemap::getTilePos(position.x, position.y);
    if (world->tilemap.map[tilePos.x][tilePos.y].type != 0) {
        vec2 pos = {(float) tilePos.x * TILE_SIZE, (float) tilePos.y * TILE_SIZE};
        float difX = position.x - pos.x;
        float difY = position.y - pos.y;
        addForce({difX * 0.5f, difY * 0.5f});
    }

    if (health <= 0) {
        destroy();
    }

    sprite.tint = {1.f, health / maxHealth, health / maxHealth};
//    if(fight){
//        attack->init();
//        attack->travel(target);
//        if(attack->position.x == target.x && attack->position.y == target.y){
//            fight = false;
//
//        }
//    }

}

void ShipObject::travel(vec2 destination) {
    vec2 position = getPosition();
    vec2 dir = {destination.x - position.x, destination.y - position.y};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > SHIP_VELOCITY) {
        dir = {dir.x / length, dir.y / length};
        this->rotation = atan2(dir.y, dir.x);
        if (abs(rotation) > M_PI / 2 + 0.1) {
            this->sprite.state = 1;
            rotation = atan2(-dir.y, -dir.x);
        } else if (abs(rotation) < M_PI / 2 - 0.1) {
            this->sprite.state = 0;
        }

        addForce({dir.x * SHIP_VELOCITY, dir.y * SHIP_VELOCITY});
    }
}

void ShipObject::collide(GameObject* obj) {
    vec2 pos = obj->getPosition();
    vec2 position = getPosition();
    float difX = position.x - pos.x;
    float difY = position.y - pos.y;
    float mul = 0.05f;

    if (!obj->playerControlled) {
        obj->health -= 10;
        mul = 0.2f;
    }

    addForce({difX * mul, difY * mul});
}