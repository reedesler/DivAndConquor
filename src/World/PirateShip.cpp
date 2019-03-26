#include "GameObject.hpp"

#define SHIP_VELOCITY 1

PirateShip::PirateShip(World* world, vec2 loc) : GameObject(world, loc) {
    w = 100;
    h = 100;
    ticks = std::rand() % 120;
    if (!sprite.init(w, h, textures_path("pirateship.png"), {0.5f, 1.f})) {
        printf("ERROR initializing sprite\n");
    }
    canShoot = true;
    rotation = 0;
    scale = {1.f, 1.f};
    landUnit = false;
    playerControlled = false;
    pathfinder = new Pathfinder(world, landUnit, true);
    health = maxHealth = 100;
    world->pirateStrength++;
}

void PirateShip::update() {
    vec2 position = getPosition();
    GameObject::update();
    if (ticks % 120 == 0) {
        GameObject* o = world->getClosestObject(position, true, false);

        if (o) {
            vec2 targetPos = o->getPosition();
            TilePos start = Tilemap::getTilePos(position.x, position.y);
            TilePos goal = Tilemap::getTilePos(targetPos.x, targetPos.y);
            pathfinder->init(start.x, start.y, goal.x, goal.y);
            pathfinder->replan();
            path = pathfinder->getPath();
        }
        world->fireOnClosestObject(this, true, true);


    }


    if (!path.path.empty()) {
        auto next = std::next(path.path.begin());
        if (next != path.path.end()) {
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

    TilePos tilePos = Tilemap::getTilePos(position.x, position.y);
    if (world->tilemap.map[tilePos.x][tilePos.y].type != 0) {
        vec2 pos = {(float) tilePos.x * TILE_SIZE, (float) tilePos.y * TILE_SIZE};
        float difX = position.x - pos.x;
        float difY = position.y - pos.y;
        addForce({difX * 0.5f, difY * 0.5f});
    }

    if (health <= 0) {
        if(world->lock == this){
            world->lock = nullptr;
        }
        destroy();
    }

    sprite.tint = {1.f, health / maxHealth, health / maxHealth};
}

void PirateShip::travel(vec2 destination) {
    vec2 position = getPosition();
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

        addForce({dir.x * SHIP_VELOCITY, dir.y * SHIP_VELOCITY});
    }
}

void PirateShip::collide(GameObject* obj) {
    vec2 pos = obj->getPosition();
    vec2 position = getPosition();
    float difX = position.x - pos.x;
    float difY = position.y - pos.y;
    float mul = 0.05f;

    if (obj->playerControlled) {
        obj->health -= 7;
        mul = 0.2f;
    }

    addForce({difX * mul, difY * mul});
}