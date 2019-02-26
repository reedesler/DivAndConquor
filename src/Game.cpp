#include "Game.hpp"
#include "Common.hpp"

#include <iostream>
#include <string>

void Game::update(float time)
{
    world->update(time);
}

void Game::draw(const mat3 &projection, int pixelScale)
{
    world->draw(pixelScale);
    glViewport(0, 0, screen.x, screen.y); // reset viewport
    // buttons probably shouldnt have their own viewport
    // after all, what if we want alert boxes or some menu that involves buttons over the world
    for (auto &it : buttons)
    {
        it.Draw(projection);
    }
}

void invokeBuildShip(Game *game, int button, int action, double xpos, double ypos)
{
    printf("invokeBuildShip! \n");
    game->buildShip();
}

void invokeHireSailors(Game *game, int button, int action, double xpos, double ypos)
{
    printf("hireSailors!\n");
    //    mat3 pos = {{1.f, 0.f, (float)xpos},
    //                {0.f, 1.f, (float)ypos},
    //                {0.f,0.f,1.f}};
    //    p.draw(pos);
}

void invokeSubmitJourney(int button, int action, double xpos, double ypos)
{
    printf("Starting a journey from a to b!\n");
    // find the two selected settlements that represent the src and dst
}

void Game::buildShip()
{
    this->balance -= 500;
    printf("balance %d\n", balance);
    this->fleet.insert(new Ship(proa));
}

void Game::init(vec2 screen)
{
    this->screen = screen;

    world = new World({0, 200, (GLint)screen.x, (GLint)screen.y - 200});

    Sprite build_ship_button = Sprite();
    if (!build_ship_button.init(120, 90, buttons_path("build_ship.png")))
    {
        printf("ERROR initializing sprite\n");
    }

    Sprite hire_sailors_button = Sprite();
    if (!hire_sailors_button.init(120, 90, buttons_path("hire_sailors.png")))
    {

        printf("ERROR initializing sprite\n");
    }

    balance = 5000;

    registerButton(build_ship_button, {80.f, 100.f}, invokeBuildShip);
    registerButton(hire_sailors_button, {80.f, 500.f}, invokeHireSailors);

    //auto characters = loadFont("data/fonts/Carlito-Bold.ttf");

    //renderText(characters, "std::string", vec2{20.f, 20.f}, 1.0, vec3{0.f, 200.f, 0.f});
    //renderText(characters, "This is sample text", vec2{25.0f, 25.0f}, 1.0f, vec3{0.5, 0.8f, 0.2f});
}

bool Game::registerButton(Sprite &btn, vec2 location, Button::OnClickFunc callback)
{
    buttons.emplace_back(btn, location, callback);
    return true;
}

// TODO: this doesn't seem to account for viewport size... y positions seem a bit off
void Game::onClick(int button, int action, double xpos, double ypos)
{
    //printf("falled in the region? %lf %lf\n", xpos, ypos);
    if (action == GLFW_PRESS)
    {
        for (auto &it : buttons)
        {

            if (it.InBounds({(float)xpos, (float)ypos}))
            {
                it.OnClick(this, 0, xpos, ypos);
                if (selectedSprites.find(&it.sprite) == selectedSprites.end())
                {
                    selectedSprites.insert(&it.sprite);
                }
                else
                {
                    selectedSprites.erase(&it.sprite);
                }
            }
        }
    } /* else if (action == GLFW_RELEASE) {

    }*/

    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h)
    {
        world->onClick(button, action, viewX, viewY);
    }
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
        case GLFW_KEY_W:
            world->pirate.moveUp = true;
            break;
        case GLFW_KEY_S:
            world->pirate.moveDown = true;
            break;
        case GLFW_KEY_A:
            world->pirate.moveLeft = true;
            break;
        case GLFW_KEY_D:
            world->pirate.moveRight = true;
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
        case GLFW_KEY_W:
            world->pirate.moveUp = false;
            break;
        case GLFW_KEY_S:
            world->pirate.moveDown = false;
            break;
        case GLFW_KEY_A:
            world->pirate.moveLeft = false;
            break;
        case GLFW_KEY_D:
            world->pirate.moveRight = false;
            break;
        default:
            break;
        }
    }

    world->camera.move(cameraDir, cameraZoom);
}
