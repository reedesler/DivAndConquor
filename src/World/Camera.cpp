#include "Camera.hpp"

Camera::Camera(rect viewPort, unsigned int worldWidth, unsigned int worldHeight, int tileSize) : worldWidth(worldWidth),
                                                                                                 worldHeight(
                                                                                                         worldHeight),
                                                                                                 tileSize(tileSize) {
    actualPos = pos = {0, 0};
    vel = {0, 0};
    zoomVel = 0;
    actualZoom = zoom = 0.5;

    this->viewPort = viewPort;
}

void Camera::update() {
    pos.x += vel.x / zoom;
    pos.y += vel.y / zoom;
    if (zoomVel > 0) {
        zoom *= zoomVel;
    } else if (zoomVel < 0) {
        zoom /= -zoomVel;
    }
    
    if(fabs(actualZoom - zoom) > 0.001f ){
        actualZoom = actualZoom * 0.85f + zoom * 0.15f;
    }

    if((actualPos.x * actualPos.y + pos.x * pos.y) > 0.1f ){
        actualPos.x = actualPos.x * 0.85f + pos.x * 0.15f;
        actualPos.y = actualPos.y * 0.85f + pos.y * 0.15f;
    }
    enforceConstraints();
}

void Camera::enforceConstraints() {

    if (zoom < 0.1) zoom = 0.1;
    if (zoom > 2) zoom = 2;
    if (actualZoom < 0.1) actualZoom = 0.1;
    if (actualZoom > 2) actualZoom = 2;
    boundCameraToWorld();
}

void Camera::move(vec2 dir, float zoom) {
    const float CAMERA_SPEED = 5;
    const float CAMERA_ZOOM = 1.01;
    vel.x += dir.x * CAMERA_SPEED;
    vel.y += dir.y * CAMERA_SPEED;
    zoomVel += zoom * CAMERA_ZOOM;
}

void Camera::moveTo(vec2 target) {
    //vel = {0,0};
    pos=target;
    enforceConstraints();
}

mat3 Camera::getProjection(int pixelScale) {
    glViewport(viewPort.x * pixelScale, viewPort.y * pixelScale, viewPort.w * pixelScale, viewPort.h * pixelScale);
    float left = 0.f;
    float top = 0.f;
    float right = viewPort.w;
    float bottom = viewPort.h;

    float sx = 2.f / (right - left);
    float sy = 2.f / (top - bottom);
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    mat3 projection_2D{{sx,  0.f, 0.f},
                       {0.f, sy,  0.f},
                       {tx,  ty,  1.f}};
    mat3 T = {{1.f,    0.f,    0.f},
              {0.f,    1.f,    0.f},
              {-actualPos.x, -actualPos.y, 1.f}};
    mat3 S = {{actualZoom, 0.f,  0.f},
              {0.f,  actualZoom, 0.f},
              {0.f,  0.f,  1.f}};
    mat3 camT = {{1.f,              0.f,              0.f},
                 {0.f,              1.f,              0.f},
                 {viewPort.w / 2.f, viewPort.h / 2.f, 1.f}};
    mat3 newProjection = mul(mul(mul(projection_2D, camT), S), T);
    return newProjection;
}

bounds Camera::getCameraBounds() {
    float left = actualPos.x - viewPort.w / 2.f / actualZoom;
    float right = actualPos.x + viewPort.w / 2.f / actualZoom;
    float top = actualPos.y - viewPort.h / 2.f / actualZoom;
    float bottom = actualPos.y + viewPort.h / 2.f / actualZoom;
    return {left, right, top, bottom};
}
bounds Camera::getCameraBoundsFor(vec2 vec) {
    float left = vec.x - viewPort.w / 2.f / actualZoom;
    float right = vec.x + viewPort.w / 2.f / actualZoom;
    float top = vec.y - viewPort.h / 2.f / actualZoom;
    float bottom = vec.y + viewPort.h / 2.f / actualZoom;
    return {left, right, top, bottom};
}

vec2 Camera::viewToWorld(vec2 mouse) {
    return {actualPos.x + (-viewPort.w / 2.f + mouse.x) / actualZoom, actualPos.y + (-viewPort.h / 2.f + mouse.y) / actualZoom};
}

void Camera::boundCameraToWorld() {
    pos = boundVecToWorld(pos);
}

vec2 Camera::boundVecToWorld(vec2 initial) {




    bounds b = getCameraBoundsFor(initial);

    float topLeftBorder = 0 - tileSize / 2.f;
    if (b.left < topLeftBorder) {
        initial.x += topLeftBorder - b.left;
    }

    float rightBorder = worldWidth * tileSize - tileSize / 2.f;
    if (b.right > rightBorder) {
        initial.x += rightBorder - b.right;
    }

    if (b.top < topLeftBorder) {
        initial.y += topLeftBorder - b.top;
    }

    float bottomBorder = worldHeight * tileSize - tileSize / 2.f;
    if (b.bottom > bottomBorder) {
        initial.y += bottomBorder - b.bottom;
    }
    return initial;
}

