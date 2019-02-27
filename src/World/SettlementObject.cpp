//
// Created by veshuga on 2019-02-26.
//

#include "GameObject.hpp"

SettlementObject::SettlementObject(World *world, vec2 loc): GameObject(world){
    this->w = 200;
    this->h = 200;
    if (!sprite.init(w, h, textures_path("settlement.png"), {1.f, 1.f}))
    {
        printf("ERROR initializing sprite\n");
    }
    this->position = loc;
    this->rotation = 0;
    this->scale = {1.f, 1.f};
}

void SettlementObject::move(vec2 pos) {
}
void SettlementObject::update() {
}