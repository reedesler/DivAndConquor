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
    w = 75;
    h = 75;

    if (!sprite.init(w, h, textures_path("sailor.png"), {0.33f, 0.25f}))
    {
        printf("ERROR initializing sprite\n");
    }
    rotation = 0;
    scale = {1.f, 1.f};
    this->settlement = settlement;
    landUnit = true;
    pathfinder = new Pathfinder(world, landUnit);
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
    vec2 position = getPosition();
    world->setExplored(position, 7 * TILE_SIZE);
    if (!path.path.empty()) {
        auto next = std::next(path.path.begin());
        if (next == path.path.end()) return;
        float destX = next->x * TILE_SIZE;
        float destY = next->y * TILE_SIZE;
        if (abs(position.x - destX) <= SAILOR_VELOCITY && abs(position.y - destY) <= SAILOR_VELOCITY) {
            pathfinder->updateStart(next->x, next->y);
            pathfinder->replan();
            path = pathfinder->getPath();
        } else {
            travel({destX, destY});
        }
    }
}

void Sailor::travel(vec2 destination) {
    vec2 position = getPosition();
    vec2 dir = {destination.x - position.x, destination.y - position.y};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > SAILOR_VELOCITY) {

        renderDirection(dir);

        dir = {dir.x / length, dir.y / length};

        vec2 newPos = {position.x + dir.x * SAILOR_VELOCITY, position.y + dir.y * SAILOR_VELOCITY};
        position = newPos;
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
