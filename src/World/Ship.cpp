//
// Created by veshuga on 2019-02-24.
//

#include "Ship.hpp"

Ship::Ship(World *world, vec2 loc, vec2 size): world(world){
        w = size.x;
        h = size.y;
        if (!sprite.init(w, h, textures_path("ship.png")))
        {
                printf("ERROR initializing sprite\n");
        }
        position = loc;
        rotation = 0;
        scale = {1.f, 1.f};
        velocity = 0;
        destination = loc;
}

void Ship::draw(const mat3 &projection)
{
        sprite.draw(projection, position, rotation, scale);
}

bounds Ship::getBounds() {
        return {position.x - w / 2, position.x + w / 2, position.y - h / 2, position.y + h / 2};
}

void Ship::move(vec2 pos) {
        position = pos;
}

void Ship::update() {
        world->setExplored(position, 7 * TILE_SIZE);
}
