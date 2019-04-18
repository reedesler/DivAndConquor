//
// Created by Tomer Torgeman on 2019-02-20.
//

#include <cmath>
#include "Common.hpp"
#include "World/GameObject.hpp"
#define VELOCITY 1

Texture Pirate::pirate_texture;
int ANIMATION_SPEED;
const int NUM_FRAMES = 3;
float ANIMATION_FRAME_H = 0.75f;
float ANIMATION_FRAME_W = 0.33f;
float Frame = 0.5f;
#define PIRATE_VELOCITY 5


Pirate::Pirate(World *world, vec2 pos): GameObject(world, pos){
    w = 56;
    h = 75;
    if (!sprite.init(w, h, textures_path("captain.png"), {0.33f, 0.25f}))
    {
        printf("ERROR initializing sprite\n");
    }
    rotation = 0;
    scale = {1.f, 1.f};
    selected = false;
    playerControlled = false;
   // playerControlled = false;
    enemy = true;
    //init();
    //this->settlement = settlement;
    landUnit = true;
    canShoot = true;
    pathfinder = new Pathfinder(world, landUnit);
    fight = false;
    health = maxHealth = 400;
    //world->pirateStrength++;


}

void Pirate::update() {
    vec2 position = getPosition();
    GameObject::update();

//    if (world->state == flee){
//        GameObject* o = world->getClosestObject(position, true, true);
//        if (o && abs(o->position.x - position.x) < 800 && abs(o->position.y - position.y) < 800) {
//            vec2 targetPos = o->getPosition();
//            TilePos start = Tilemap::getTilePos(position.x, position.y);
//            TilePos goal = Tilemap::getTilePos(world->w - 100, world->h - 100);
//            pathfinder->init(start.x, start.y, goal.x - 400, goal.y - 400);
//            pathfinder->replan();
//            path = pathfinder->getPath();
//        }
//    }

    TilePos start;
    TilePos goal;
    if (ticks % 120 == 0) {
        GameObject* o = world->getClosestObject(position, true, true);

        if (o && world->state != flee) {
            vec2 targetPos = o->getPosition();
             start = Tilemap::getTilePos(position.x, position.y);
             goal = Tilemap::getTilePos(targetPos.x-20, targetPos.y-20);
//            pathfinder->init(start.x, start.y, goal.x, goal.y);
//            pathfinder->replan();
//            path = pathfinder->getPath();
        }
        world->fireOnClosestObject(this, true, true);


    }


    //if (!path.path.empty()) {
       // auto next = std::next(path.path.begin());
       // if (next != path.path.end()) {
            //float destX = next->x * TILE_SIZE;
           // float destY = next->y * TILE_SIZE;
//            if (abs(position.x - destX) <= VELOCITY && abs(position.y - destY) <= VELOCITY) {
//                pathfinder->updateStart(next->x, next->y);
//                pathfinder->replan();
//                path = pathfinder->getPath();
//            } else {
                //travel({goal->x, goal->y});
//            }
//        }
   // }
    GameObject* o = world->getClosestObjectOnLand(position, true, true);
    if(o){
        travel({o->position.x, o->position.y});

    }
//    //TilePos tilePos = Tilemap::getTilePos(o->position.x, o->position.y);
//    if (o) {
//        vec2 pos = {(float) o->position.x * TILE_SIZE, (float) o->position.y * TILE_SIZE};
//        float difX = position.x - pos.x;
//        float difY = position.y - pos.y;
//        addForce({difX * 0.5f, difY * 0.5f});
//    }

    if (health <= 0) {
        if(world->lock == this){
            world->lock = nullptr;
        }
        //world->pirateStrength--;
        destroy();
    }

    sprite.tint = {1.f, health / maxHealth, health / maxHealth};
}

void Pirate::travel(vec2 destination) {
    vec2 position = getPosition();
    vec2 dir = {destination.x - position.x, destination.y - position.y};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > VELOCITY) {

        renderDirection(dir);

        dir = {dir.x / length, dir.y / length};

        addForce({dir.x * VELOCITY, dir.y * VELOCITY});
    }
}

void Pirate::renderDirection(vec2 dir){
    if(frameNo > 1){
        frameNo = 0;
    }
    if(dir.x > 0 && abs(dir.x)  > abs(dir.y)){
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.25f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    } else if (dir.x < 0){
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.75f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    } else if (dir.y > 0 && abs(dir.x) < abs(dir.y)){
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.5f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    } else {
        this->sprite.state = 1;
        this->sprite.texPiece.x =0.f + frameNo;
        this->sprite.texPiece.y = 0.f;
        this->sprite.frame.x = 0.3f;
        this->sprite.frame.y = 0.25f;
    }

    if (r % 3 == 0){
        frameNo = frameNo + 0.333f;
    }
}
