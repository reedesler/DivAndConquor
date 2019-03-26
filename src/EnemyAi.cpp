//
// Created by Tomer Torgeman on 2019-03-21.
//

//#include <tkDecls.h>
#include "EnemyAi.h"


void EnemyAi::setState(World* world){

if(world->navalStrength > 3){
    world->state = invade;
}

if (world->wealth > 5){
    world->state = invade;
}



giveOrder(world);
};

void EnemyAi::giveOrder(World* world){

    switch (world->state){
        case explore:

            break;
        case invade:

            for (int i = 0; i < world->navalStrength + 1; ++i) {
                world->gameObjects.push_back(new PirateShip(world, {2300, 1300}));
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