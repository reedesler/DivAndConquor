//
// Created by Tomer Torgeman on 2019-03-21.
//

#ifndef DIVCONQ_ENEMYAI_H
#define DIVCONQ_ENEMYAI_H

#include <World/GameObject.hpp>
//#include "Game.hpp"

enum State {
    invade,
    explore,
    flee,

};
class EnemyAi {

public:
    void setState(World*);

    void giveOrder();

    State state;


};


#endif //DIVCONQ_ENEMYAI_H
