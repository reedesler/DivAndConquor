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

    Sprite build_ship_button =  Sprite();
    if (!build_ship_button.init(120, 90, buttons_path("build_ship.png"))) {
        printf("ERROR initializing sprite\n");
    }

    Sprite hire_sailors_button =  Sprite();
    if (!hire_sailors_button.init(120, 90, buttons_path("hire_sailors.png"))) {
        printf("ERROR initializing sprite\n");
    }

    balance = 5000;

    registerButton(build_ship_button, {80.f, 100.f}, invokeBuildShip);
    registerButton(hire_sailors_button, {80.f, 200.f}, invokeHireSailors);
}

void Game::update() {
    world->update();
}

void Game::draw(const mat3 &projection, int pixelScale) {

    world->draw(pixelScale);
    for (auto &it : buttons) {
        it.Draw(projection);
    }

}

bool Game::registerButton(Sprite &btn, vec2 location, Button::OnClickFunc callback) {
    buttons.emplace_back(btn, location, callback);
    return true;
}

/*
bool Game::removeButton(Sprite* btn) {
    buttonCallbacks.erase(btn);
    return true;
}
*/
// TODO: this doesn't seem to account for viewport size... y positions seem a bit off
void Game::onClick(int button, int action, double xpos, double ypos) {
    //printf("falled in the region? %lf %lf\n", xpos, ypos);
    if (action == GLFW_PRESS) {
        for (auto &it : buttons) {

            if(it.InBounds({(float)xpos,(float)ypos})) {
                it.OnClick(0, xpos, ypos);
                if (selectedSprites.find(&it.sprite) == selectedSprites.end()) {
                    selectedSprites.insert(&it.sprite);
                } else {
                    selectedSprites.erase(&it.sprite);
                }
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
