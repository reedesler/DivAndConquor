//
// Created by Reed on 2019-01-29.
//

#ifndef DIVCONQ_CAMERA_H
#define DIVCONQ_CAMERA_H


#include <SDL_events.h>
#include "draw_context.h"

class Camera {
public:
    Camera(SDL_Rect viewPort, DrawContext* pContext);

    void update();

    void draw(DrawContext* dc);

    void handleInput(SDL_Event &event);

    SDL_Rect transform(SDL_Rect r);

    void drawRect(SDL_Rect rect, SDL_Color color);

private:
    float x, y;
    SDL_Rect viewPort;
    float zoom;
    float velX, velY, velZoom;
    DrawContext* dc;
};


#endif //DIVCONQ_CAMERA_H
