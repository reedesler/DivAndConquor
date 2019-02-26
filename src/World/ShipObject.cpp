//
// Created by veshuga on 2019-02-24.
//

#include "GameObject.hpp"

ShipObject::ShipObject(World *world, vec2 loc): GameObject(world){
        w = 100;
        h = 100;
        if (!sprite.init(w, h, textures_path("ship.png")))
        {
                printf("ERROR initializing sprite\n");
        }
        position = loc;
        rotation = 0;
        scale = {1.f, 1.f};
        velocity = 5;
        destination = loc;
}

void ShipObject::move(vec2 pos) {
        this->destination = pos;
       // this->velocity = 5;

}

void ShipObject::update() {
        world->setExplored(position, 7 * TILE_SIZE);
        if (abs(position.x - destination.x) - 5 > 0 || abs(position.y - destination.y) - 5 > 0)
                this->travel();
}

void ShipObject::travel() {
        vec2 dir =  {destination.x - position.x, destination.y - position.y};
        float length = sqrt(dir.x*dir.x + dir.y*dir.y);
        vec2 newPos = {position.x + dir.x / length * velocity, position.y + dir.y / length * velocity};
        bool tmp = onTerrain(newPos, 0);
        if (!tmp)
                destination = position;
        else
                position = newPos;
}