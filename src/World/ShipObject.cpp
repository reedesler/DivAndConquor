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
        velocity = 0;
        destination = loc;
}