#include "Game.hpp"

void Game::init(vec2 screen) {
    world = new World({0, 200, (GLint) screen.x, (GLint) screen.y - 200});
}

void Game::update() {
    world->update();
}

void Game::draw(const mat3& projection, int pixelScale) {
    world->draw(projection, pixelScale);
}

void Game::onKey(int key, int scancode, int action) {
    vec2 cameraDir = {0, 0};
    int cameraZoom = 0;
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP: cameraDir.y -= 1; break;
            case GLFW_KEY_DOWN: cameraDir.y += 1; break;
            case GLFW_KEY_LEFT: cameraDir.x -= 1; break;
            case GLFW_KEY_RIGHT: cameraDir.x += 1; break;
            case GLFW_KEY_COMMA: cameraZoom -= 1; break;
            case GLFW_KEY_PERIOD: cameraZoom += 1; break;
            default: break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_UP: cameraDir.y += 1; break;
            case GLFW_KEY_DOWN: cameraDir.y -= 1; break;
            case GLFW_KEY_LEFT: cameraDir.x += 1; break;
            case GLFW_KEY_RIGHT: cameraDir.x -= 1; break;
            case GLFW_KEY_COMMA: cameraZoom += 1; break;
            case GLFW_KEY_PERIOD: cameraZoom -= 1; break;
            default: break;
        }
    }

    world->moveCamera(cameraDir, cameraZoom);
}
