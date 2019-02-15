#include "World.hpp"

World::World() {
    gameObjects.push_back(new GameObject());
    cameraPos = {0, 0};
    cameraVel = {0, 0};
    cameraZoomVel = 0;
    cameraZoom = 1;
}

void World::update() {
    cameraPos.x += cameraVel.x;
    cameraPos.y += cameraVel.y;
    if (cameraZoomVel > 0) {
        cameraZoom *= cameraZoomVel;
    } else if (cameraZoomVel < 0) {
        cameraZoom /= -cameraZoomVel;
    }
}

void World::draw(const mat3 &projection) {
    mat3 T = { { 1.f, 0.f, 0.f },{ 0.f, 1.f, 0.f },{ -cameraPos.x, -cameraPos.y, 1.f } };
    mat3 S = { { cameraZoom, 0.f, 0.f },{ 0.f, cameraZoom, 0.f },{ 0.f, 0.f, 1.f } };
    mat3 newProjection = mul(mul(projection, T), S);
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
