//
// Created by Reed on 2019-01-29.
//

#include "Camera.h"

static const int CAM_VEL = 10;

Camera::Camera(SDL_Rect viewPort, DrawContext* dc) : viewPort(viewPort), dc(dc) {
    x = 0;
    y = 0;
    velX = 0;
    velY = 0;
}

void Camera::handleInput(SDL_Event &event) {
    //If a key was pressed
    if( event.type == SDL_KEYDOWN && event.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: velY -= CAM_VEL; break;
            case SDLK_DOWN: velY += CAM_VEL; break;
            case SDLK_LEFT: velX -= CAM_VEL; break;
            case SDLK_RIGHT: velX += CAM_VEL; break;
        }
    }
        //If a key was released
    else if( event.type == SDL_KEYUP && event.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: velY += CAM_VEL; break;
            case SDLK_DOWN: velY -= CAM_VEL; break;
            case SDLK_LEFT: velX += CAM_VEL; break;
            case SDLK_RIGHT: velX -= CAM_VEL; break;
        }
    }
}

void Camera::update() {
    x += velX;
    y += velY;
}

SDL_Rect Camera::transform(SDL_Rect r) {
    return {dc->floatToPixel(r.x - x), dc->floatToPixel(r.y - y), r.w, r.h};
}

void Camera::draw(DrawContext* dc) {
    dc->setViewport(viewPort);
    dc->drawRect({0, 0, viewPort.w, viewPort.h}, {255, 255, 255, 255});
}

void Camera::drawRect(SDL_Rect rect, SDL_Color color) {
    dc->drawRect(transform(rect), color);
}
