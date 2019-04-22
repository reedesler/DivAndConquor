//
// Created by veshuga on 2019-03-08.
//

#include "GameObject.hpp"
#include <sstream>


Resource::Resource(World *world, vec2 loc, uint16_t type, int size) : GameObject(world, loc) {
    w = 50;
    h = 50;
    if (type == 0) {
        if (!sprite.init(w, h, textures_path("gold.png"), {1.f, 1.f}))
            printf("ERROR initializing sprite\n");
    } else if (type == 1){
        if (!sprite.init(w, h, textures_path("iron.png"), {1.f, 1.f}))
            printf("ERROR initializing sprite\n");
    } else {
        if (!sprite.init(w, h, textures_path("timber.png"), {1.f, 1.f}))
            printf("ERROR initializing sprite\n");
    }
    playerControlled = false;
    landUnit = true;
    loot_type = type;
    resource = size;
    health = maxHealth = 0.f;
}
std::string Resource::getName(){

    if (loot_type == 0) {
        return "gold";
    } else if (loot_type == 1){
        return "iron";
    } else if (loot_type==2) {
        return "timber";
    } else {
        return "UNKNOWN";
    }
}

bool Resource::collect(Game* game, Sailor *obj) {
    bounds other = obj->getBounds();
    vec2 position = getPosition();
    if (position.x >= other.left && position.x <= other.right)
        if (position.y >= other.top && position.y <= other.bottom){
            obj->settlement->updateResources(this->loot_type, this->resource);
            world->wealth++;
            std::ostringstream str;
            str << "Collected " << this->resource << " " << this->getName();
            game->printLn(str.str());
            return true;
        }
    return false;
}
