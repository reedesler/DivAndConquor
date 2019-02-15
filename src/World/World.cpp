#include "World.hpp"

World::World()
{
    gameObjects.push_back(new GameObject());
    cameraPos = {0, 0};
    cameraVel = {0, 0};
}

void World::update()
{
    cameraPos.x += cameraVel.x;
    cameraPos.y += cameraVel.y;
}

void World::draw(const mat3 &projection)
{
    mat3 T = {{1.f, 0.f, 0.f}, {0.f, 1.f, 0.f}, {-cameraPos.x, -cameraPos.y, 1.f}};
    mat3 newProjection = mul(projection, T);
    for (auto o : gameObjects)
    {
        o->draw(newProjection);
    }
}

void World::moveCamera(vec2 dir)
{
    const float CAMERA_SPEED = 20;
    cameraVel.x += dir.x * CAMERA_SPEED;
    cameraVel.y += dir.y * CAMERA_SPEED;
}
