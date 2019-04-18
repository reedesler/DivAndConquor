//
// Created by Tomer Torgeman on 2019-03-21.
//

//#include <tkDecls.h>
#include "EnemyAi.h"


void EnemyAi::updateState(World *world) {

    if (world->navalStrength > 3) {
        world->state = invade;
    }

    if (world->wealth > 5) {
        world->state = invade;
    }

    if(world->pirateStrength < (world->navalStrength/2)){
        world->state = flee;
        printf("fleestate");
    }

    if (world->state != neutral && world->state != invade){
        if(world->pirateStrength > (world->navalStrength/2)){
            world->state = neutral;
            printf("neutralstate");
        }
    }


    giveOrder(world);
};

void EnemyAi::giveOrder(World *world) {

    switch (world->state) {
        case explore:

            break;
        case invade:

            for (int i = 0; i < world->navalStrength + 1; ++i) {
                float x = std::rand() % (world->w - 100);
                float y = std::rand() % (world->h - 100);
                while (world->tilemap.getTile(x, y).type != 0)
                {
                    x = std::rand() % (world->w - 100);
                    y = std::rand() % (world->h - 100);
                }
                world->gameObjects.push_back(new PirateShip(world, {x, y}));
                printf("enemy added");
            }
            world->wealth = 0;
            world->navalStrength = 0;
            world->state = neutral;

            break;
        case flee:


            break;

        case neutral:
            break;

    }
};

//void World::addPirateShips()
//{
//    if(pirateStrength < 3){
//        printf("Adding pirates\n");
//        for (int i = 0; i < 1; i++){
//            float x = std::rand() % (this->w - 100);
//            float y = std::rand() % (this->h - 100);
//            while (tilemap.getTile(x, y).type != 0)
//            {
//                x = std::rand() % (this->w - 100);
//                y = std::rand() % (this->h - 100);
//            }
//            gameObjects.push_back(new PirateShip(this, {x, y}));
//        }
//
//
//    }
//
//}
