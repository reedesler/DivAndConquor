//
// Created by veshuga on 2019-02-24.
//

#include "GameObject.hpp"

ShipObject::ShipObject(World *world, vec2 loc): GameObject(world){
        w = 100;
        h = 100;
        if (!sprite.init(w, h, textures_path("ship.png"), {0.5f, 1.f}))
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
        vec2 dir =  {destination.x - position.x, destination.y - position.y};
        float length = sqrt(dir.x*dir.x + dir.y*dir.y);
        if (length > 5){
                dir = {dir.x / length, dir.y / length};
                this->travel(dir);
                this->rotation = atan2(dir.y , dir.x);
                if(abs(rotation) > M_PI / 2) {
                        this->sprite.state = 1;
                        rotation = atan2(-dir.y, -dir.x);
                }
                else
                        this->sprite.state = 0;
                //printf ("%f : %f\n", position.x, position.y);
        }
}

void ShipObject::travel(vec2 dir) {
        vec2 newPos = {position.x + dir.x * velocity, position.y + dir.y * velocity};
        bool tmp = onTerrain(newPos, 0);
        if (!tmp)
                destination = position;
        else
                position = newPos;
}