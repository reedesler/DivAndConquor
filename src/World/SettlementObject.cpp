//
// Created by veshuga on 2019-02-26.
//

#include "GameObject.hpp"

SettlementObject::SettlementObject(World *world, vec2 loc): GameObject(world, loc){
    this->w = 200;
    this->h = 200;
    if (!sprite.init(w, h, textures_path("settlement.png"), {1.f, 1.f}))
    {
        printf("ERROR initializing sprite\n");
    }
    this->rotation = 0;
    this->scale = {1.f, 1.f};
    this->gold = 500;
    this->iron = 500;
    this->timber = 500;
    canShoot = false;
    health = 200;

}

void SettlementObject::move(vec2 pos) {
}
void SettlementObject::update() {
    world->setExplored(getPosition(), 15 * TILE_SIZE);
    if (health <= 0) {
//        if(world->lock == this){
//            world->lock = nullptr;
//        }
        destroy();
    }
}
void SettlementObject::updateResources(uint16_t type, int amount) {
    if (type == 0)
        this->gold += amount;
    else if (type == 1)
        this->iron += amount;
    else if (type == 2)
        this->timber += amount;
    printf("sett: %p g:%d i:%d t:%d\n", this, this->gold, this->iron, this->timber);
}

vec3 SettlementObject::getResources() {
    return {(float) this->gold, (float) this->iron, (float) this->timber};
}