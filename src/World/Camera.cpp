#include "Camera.hpp"

Camera::Camera(rect viewPort, unsigned int worldWidth, unsigned int worldHeight, int tileSize) : worldWidth(worldWidth),
                                                                                                 worldHeight(
                                                                                                         worldHeight),
                                                                                                 tileSize(tileSize) {
    pos = {0, 0};
    vel = {0, 0};
    zoomVel = 0;
    zoom = 0.5;
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

    boundCameraToWorld();
}

void Camera::move(vec2 dir, float zoom) {
    const float CAMERA_SPEED = 5;
    const float CAMERA_ZOOM = 1.01;
    vel.x += dir.x * CAMERA_SPEED;
    vel.y += dir.y * CAMERA_SPEED;
    zoomVel += zoom * CAMERA_ZOOM;
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
              {-pos.x, -pos.y, 1.f}};
    mat3 S = {{zoom, 0.f,  0.f},
              {0.f,  zoom, 0.f},
              {0.f,  0.f,  1.f}};
    mat3 camT = {{1.f,              0.f,              0.f},
                 {0.f,              1.f,              0.f},
                 {viewPort.w / 2.f, viewPort.h / 2.f, 1.f}};
    mat3 newProjection = mul(mul(mul(projection_2D, camT), S), T);
    return newProjection;
}

bounds Camera::getCameraBounds() {
    float left = pos.x - viewPort.w / 2.f / zoom;
    float right = pos.x + viewPort.w / 2.f / zoom;
    float top = pos.y - viewPort.h / 2.f / zoom;
    float bottom = pos.y + viewPort.h / 2.f / zoom;
    return {left, right, top, bottom};
}

vec2 Camera::viewToWorld(vec2 mouse) {
    return {pos.x + (-viewPort.w / 2.f + mouse.x) / zoom, pos.y + (-viewPort.h / 2.f + mouse.y) / zoom};
}

void Camera::boundCameraToWorld() {

    if (zoom < 0.1) zoom = 0.1;
    if (zoom > 2) zoom = 2;

    bounds b = getCameraBounds();

    float topLeftBorder = 0 - tileSize / 2.f;
    if (b.left < topLeftBorder) {
        pos.x += topLeftBorder - b.left;
    }

    float rightBorder = worldWidth * tileSize - tileSize / 2.f;
    if (b.right > rightBorder) {
        pos.x += rightBorder - b.right;
    }

    if (b.top < topLeftBorder) {
        pos.y += topLeftBorder - b.top;
    }

    float bottomBorder = worldHeight * tileSize - tileSize / 2.f;
    if (b.bottom > bottomBorder) {
        pos.y += bottomBorder - b.bottom;
    }
}
