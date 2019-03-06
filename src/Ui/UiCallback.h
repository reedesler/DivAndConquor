//
// Created by Dmitry on 2019-03-05.
//

#ifndef DIVCONQ_UICALLBACK_H
#define DIVCONQ_UICALLBACK_H


class Game;

class UiCallback {
    // OnClickFunc has a parameter list of {Game *game, int button, int action, double xpos, double ypos}
public:
    typedef void (*OnClickFunc)(Game *, int, int, double, double);

};


#endif //DIVCONQ_UICALLBACK_H
