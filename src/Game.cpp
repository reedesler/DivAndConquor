#include "Game.hpp"

void invokeBuildShip(int button, int action, double xpos, double ypos) {
    printf("invokeBuildShip!\n");
}

void invokeHireSailors(int button, int action, double xpos, double ypos) {
    printf("hireSailors!\n");
}

void Game::init(vec2 screen) {
    this->screen = screen;

    world = new World({0, 200, (GLint)screen.x, (GLint)screen.y - 200});

    Sprite* build_ship_button = new Sprite();
    if (!build_ship_button->init(120, 90, buttons_path("build_ship.png"))) {
        printf("ERROR initializing sprite\n");
    }

    Sprite* hire_sailors_button = new Sprite();
    if (!hire_sailors_button->init(120, 90, buttons_path("hire_sailors.png"))) {
        printf("ERROR initializing sprite\n");
    }

    balance = 5000;

    registerButton(build_ship_button, {0.f, 0.f}, invokeBuildShip);
    registerButton(hire_sailors_button, {0.f, 100.f}, invokeHireSailors);
}

void Game::update() {
    world->update();
}

void Game::draw(const mat3 &projection, int pixelScale) {

    for (auto it : buttonPositions) {
        assert(it.first != nullptr);
        (it.first)->draw(projection, it.second);
    }

    world->draw(pixelScale);
}

bool Game::registerButton(Sprite* btn, vec2 location, ButtonOnClickFunc callback) {
    buttonCallbacks[btn] = callback;
    buttonPositions[btn] = location;
    return true;
}

bool Game::removeButton(Sprite* btn) {
    buttonCallbacks.erase(btn);
    return true;
}

void Game::onClick(int button, int action, double xpos, double ypos) {
    //printf("falled in the region? %lf %lf\n", xpos, ypos);
    if (action == GLFW_PRESS) {
        for (auto it : buttonCallbacks) {

            if (xpos > buttonPositions[it.first].x &&
                xpos < buttonPositions[it.first].x + it.first->width &&
                ypos > buttonPositions[it.first].y &&
                ypos < buttonPositions[it.first].y + it.first->height) {
                if (selectedSprites.find(it.first) == selectedSprites.end()) {
                    selectedSprites.insert(it.first);
                } else {
                    selectedSprites.erase(it.first);
                }
                it.second(button, action, xpos, ypos);
            }
        }
    } /* else if (action == GLFW_RELEASE) {

    }*/

    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h) {
        world->onClick(button, action, viewX, viewY);
    }
}

void Game::onKey(int key, int scancode, int action) {
    vec2 cameraDir = {0, 0};
    int cameraZoom = 0;
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_UP:
                cameraDir.y -= 1;
                break;
            case GLFW_KEY_DOWN:
                cameraDir.y += 1;
                break;
            case GLFW_KEY_LEFT:
                cameraDir.x -= 1;
                break;
            case GLFW_KEY_RIGHT:
                cameraDir.x += 1;
                break;
            case GLFW_KEY_COMMA:
                cameraZoom -= 1;
                break;
            case GLFW_KEY_PERIOD:
                cameraZoom += 1;
                break;
            default:
                break;
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_UP:
                cameraDir.y += 1;
                break;
            case GLFW_KEY_DOWN:
                cameraDir.y -= 1;
                break;
            case GLFW_KEY_LEFT:
                cameraDir.x += 1;
                break;
            case GLFW_KEY_RIGHT:
                cameraDir.x -= 1;
                break;
            case GLFW_KEY_COMMA:
                cameraZoom += 1;
                break;
            case GLFW_KEY_PERIOD:
                cameraZoom -= 1;
                break;
            default:
                break;
        }
    }

    world->camera.move(cameraDir, cameraZoom);
}
