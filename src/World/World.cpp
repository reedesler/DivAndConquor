#include "World.hpp"
#include "Tilemap.h"

World::World(rect viewPort) : tilemap(Tilemap::LoadFromFile(maps_path("map1.txt"))), viewPort(viewPort) {
    gameObjects.push_back(new GameObject());
    cameraPos = {0, 0};
    cameraVel = {0, 0};
    cameraZoomVel = 0;
    cameraZoom = 1;
}

void World::update() {
    cameraPos.x += cameraVel.x / cameraZoom;
    cameraPos.y += cameraVel.y / cameraZoom;
    if (cameraZoomVel > 0) {
        cameraZoom *= cameraZoomVel;
    } else if (cameraZoomVel < 0) {
        cameraZoom /= -cameraZoomVel;
    }
}

void World::draw(const mat3 &projection, int pixelScale) {
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
    mat3 T = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ -cameraPos.x, -cameraPos.y, 1.f } };
    mat3 S = { { cameraZoom, 0.f, 0.f },{ 0.f, cameraZoom, 0.f },{ 0.f, 0.f, 1.f } };
    mat3 camT = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ viewPort.w / 2.f, viewPort.h / 2.f, 1.f } };
    mat3 newProjection = mul(mul(mul(projection_2D, camT), S), T);
    tilemap.draw(newProjection);
    for (auto o : gameObjects) {
        o->draw(newProjection);
    }
}

void World::moveCamera(vec2 dir, int zoom) {
    const float CAMERA_SPEED = 20;
    const float CAMERA_ZOOM = 1.01;
    cameraVel.x += dir.x * CAMERA_SPEED;
    cameraVel.y += dir.y * CAMERA_SPEED;
    cameraZoomVel += zoom * CAMERA_ZOOM;
}
