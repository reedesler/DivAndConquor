//
// Created by Tomer Torgeman on 2019-03-21.
//

//#include <tkDecls.h>
#include "EnemyAi.h"


void EnemyAi::setState(World* world){

if(world->navalStrength > 1){
//    world->gameObjects.push_back(new PirateShip(world, {2300, 1300}));
//    printf("enemy added");

}

};

void EnemyAi::giveOrder(){
    switch (state){
        case explore:

            break;
        case invade:

            break;
        case flee:
            break;

    }
};