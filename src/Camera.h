//
// Created by Reed on 2019-01-29.
//

#ifndef DIVCONQ_CAMERA_H
#define DIVCONQ_CAMERA_H


#include <SDL_events.h>

class Camera {
public:
    Camera();

    float x, y;

    void update();

    void handleInput(SDL_Event& event);
    float velX, velY;

private:
};


#endif //DIVCONQ_CAMERA_H
