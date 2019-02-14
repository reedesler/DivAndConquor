#include "Game.h"

void Game::init() {
    world = new World();
}

void Game::update() {
    world->update();
}

void Game::draw(const mat3& projection) {
    world->draw(projection);
}

void Game::onKey(int key, int scancode, int action) {
    vec2 cameraDir = {0, 0};
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP: cameraDir.y -= 1; break;
            case GLFW_KEY_DOWN: cameraDir.y += 1; break;
            case GLFW_KEY_LEFT: cameraDir.x -= 1; break;
            case GLFW_KEY_RIGHT: cameraDir.x += 1; break;
            default: break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_UP: cameraDir.y += 1; break;
            case GLFW_KEY_DOWN: cameraDir.y -= 1; break;
            case GLFW_KEY_LEFT: cameraDir.x += 1; break;
            case GLFW_KEY_RIGHT: cameraDir.x -= 1; break;
            default: break;
        }
    }

    world->moveCamera(cameraDir);
}
