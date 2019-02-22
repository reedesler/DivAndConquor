#include "Game.hpp"

void Game::init(vec2 screen)
{
    world = new World({0, 200, (GLint)screen.x, (GLint)screen.y - 200});

    Sprite button;
    if (!button.init(150, 100, textures_path("turtle.png")))
    {
        printf("ERROR initializing sprite\n");
    }

    registerButton(button, {20.f, 30.f}, nullptr);
}

void Game::update()
{
    world->update();
}

void Game::draw(const mat3 &projection, int pixelScale)
{
    world->draw(projection, pixelScale);

    /* for (auto it : buttonPositions)
    {
        it.first->draw(projection, it.second);
    }*/
}

bool Game::registerButton(Sprite btn, vec2 location, ButtonOnClickFunc callback)
{
    buttonCallbacks[&btn] = callback;
    buttonPositions[&btn] = location;
    return true;
}

bool Game::removeButton(Sprite btn)
{
    buttonCallbacks.erase(&btn);
    return true;
}

void Game::onClick(int button, int action, double xpos, double ypos)
{

    if (action == GLFW_PRESS)
    {
        for (auto it : buttonCallbacks)
        {
            if (xpos > buttonPositions[it.first].x &&
                xpos < buttonPositions[it.first].x + it.first->width &&
                ypos > buttonPositions[it.first].y &&
                ypos < buttonPositions[it.first].y + it.first->height)
            {
                (it.second)(button, action, xpos, ypos);
            }
        }
    } /* else if (action == GLFW_RELEASE) {

    }*/
}

void Game::onKey(int key, int scancode, int action)
{
    vec2 cameraDir = {0, 0};
    int cameraZoom = 0;
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
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
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
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

    world->moveCamera(cameraDir, cameraZoom);
}
