//
// Created by Tomer Torgeman on 2019-03-05.
//

#include "World/GameObject.hpp"
#include "Common.hpp"
//Texture Sailor::sailor_texture;

float ANIMATION_FRAME_HS = 0.75f;
float ANIMATION_FRAME_WS = 0.33f;
#define SAILOR_VELOCITY 5


Sailor::Sailor(World *world, vec2 pos, SettlementObject *settlement): GameObject(world, pos){
    w = 56;
    h = 75;

    if (!sprite.init(w, h, textures_path("sailor.png"), {0.33f, 0.25f}))
    {
        printf("ERROR initializing sprite\n");
    }
    rotation = 0;
    scale = {1.f, 1.f};
    this->settlement = settlement;
    this->settlement->updateResources(0, -100);
    landUnit = true;
    canShoot = true;
    pathfinder = new Pathfinder(world, landUnit);
    fight = false;
    health = maxHealth = 200;
    world->manPower++;
    playerControlled = true;

}

void Sailor::move(vec2 pos) {
    vec2 position = getPosition();
    TilePos start = Tilemap::getTilePos(position.x, position.y);
    TilePos goal = Tilemap::getTilePos(pos.x, pos.y);
    pathfinder->init(start.x, start.y, goal.x, goal.y);
    pathfinder->replan();
    path = pathfinder->getPath();
}

void Sailor::update() {
    GameObject::update();

    if(health < 0){
        world->manPower--;
        world->lock = nullptr;
        this->destroy();
    }

    if (ticks % 120 == 0) {

        world->fireOnClosestObject(this, false, true);
    }

//    if(world->selectedObject->attack != nullptr){
//        if(checkCollision(world->selectedObject->attack,  this)){
//            health -= 10;
//            printf("hit");
//            //world->selectedObject->attack->destroy();
//            //delete world->selectedObject->attack;
//
//        }
//    }





//    if (attack){
//        if(attack->attackCondition(fight)){
//            fight = false;
//        }
//
//
//    }

    vec2 position = getPosition();
    world->setExplored(position, 7 * TILE_SIZE);
    if (!path.path.empty()) {
        auto next = std::next(path.path.begin());
        if (next == path.path.end()) return;
        float destX = next->x * TILE_SIZE;
        float destY = next->y * TILE_SIZE;
        if (abs(position.x - destX) <= SAILOR_VELOCITY * 2 && abs(position.y - destY) <= SAILOR_VELOCITY * 2) {
            pathfinder->updateStart(next->x, next->y);
            pathfinder->replan();
            path = pathfinder->getPath();
        } else {
            travel({destX, destY});
        }
    }

    sprite.tint = {1.f, health / maxHealth, health / maxHealth};



}

void Sailor::travel(vec2 destination) {
    vec2 position = getPosition();
    vec2 dir = {destination.x - position.x, destination.y - position.y};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > SAILOR_VELOCITY) {

        renderDirection(dir);

        dir = {dir.x / length, dir.y / length};

        addForce({dir.x * SAILOR_VELOCITY, dir.y * SAILOR_VELOCITY});
    }
}

void Sailor::renderDirection(vec2 dir){
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
