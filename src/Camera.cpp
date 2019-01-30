//
// Created by Reed on 2019-01-29.
//

#include "Camera.h"

static const int CAM_VEL = 5;
static const float ZOOM_VEL = 1.01;

Camera::Camera(SDL_Rect viewPort, DrawContext* dc) : viewPort(viewPort), dc(dc) {
    x = 0;
    y = 0;
    velX = 0;
    velY = 0;
    velZoom = 0;
    zoom = 0.1;
}

void Camera::handleInput(SDL_Event &event) {
    //If a key was pressed
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: velY -= CAM_VEL; break;
            case SDLK_DOWN: velY += CAM_VEL; break;
            case SDLK_LEFT: velX -= CAM_VEL; break;
            case SDLK_RIGHT: velX += CAM_VEL; break;
            case SDLK_PERIOD: velZoom += ZOOM_VEL; break;
            case SDLK_COMMA: velZoom -= ZOOM_VEL; break;
        }
    }
    //If a key was released
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch(event.key.keysym.sym) {
            case SDLK_UP: velY += CAM_VEL; break;
            case SDLK_DOWN: velY -= CAM_VEL; break;
            case SDLK_LEFT: velX += CAM_VEL; break;
            case SDLK_RIGHT: velX -= CAM_VEL; break;
            case SDLK_PERIOD: velZoom -= ZOOM_VEL; break;
            case SDLK_COMMA: velZoom += ZOOM_VEL; break;
        }
    }
}

void Camera::update() {
    x += velX / zoom;
    y += velY / zoom;
    if (velZoom > 0) {
        zoom *= velZoom;
    } else if (velZoom < 0) {
        zoom /= -velZoom;
    }
}

SDL_Rect Camera::transform(SDL_Rect r) {
    float newX = floor(zoom * (r.x - x) + (float) viewPort.w / 2);
    float newY = floor(zoom * (r.y - y) + (float) viewPort.h / 2);
    float newW = ceil(zoom * r.w);
    float newH = ceil(zoom * r.h);
    return {static_cast<int>(newX), static_cast<int>(newY), static_cast<int>(newW), static_cast<int>(newH)};
}

void Camera::draw(DrawContext* dc) {
    dc->setViewport(viewPort);
    dc->drawRect({0, 0, viewPort.w, viewPort.h}, {255, 255, 255, 255});
}

void Camera::drawRect(SDL_Rect rect, SDL_Color color) {
    dc->drawRect(transform(rect), color);
}