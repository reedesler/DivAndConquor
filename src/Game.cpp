#include "Game.hpp"
#include "Common.hpp"

#include <iostream>
#include <string>
#define  UI_HEIGHT 150

Sprite portraitFrame;
void Game::update()
{
    world->update();
}

void Game::draw(const mat3 &projection, int pixelScale)
{
    world->draw(pixelScale);
    drawUI(projection);
    // buttons probably shouldnt have their own viewport
    // after all, what if we want alert boxes or some menu that involves buttons over the world

}

void Game::drawUI(const mat3 &projection) {
    glViewport(0, 0, screen.x, screen.y); // reset viewport

    for (auto &it : buttons)
    {
        it.Draw(projection);
    }
    portraitFrame.draw(projection,{25 + 150/2, screen.y-150/2});
}

void invokeBuildShip(Game *game, int button, int action, double xpos, double ypos)
{
    printf("invokeBuildShip! \n");

    game->buildShip(vec2{(float)xpos, (float)ypos});
}

void invokeHireSailors(Game *game, int button, int action, double xpos, double ypos)
{
//    game->world->pirate.init();
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

void Game::buildShip(vec2 location)
{
   

    (this->world)->addShip(new ShipObject(this->world, location));
}

void Game::init(vec2 screen)
{
    this->screen = screen;

    world = new World({0, 0, (GLint)screen.x, (GLint)screen.y});

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

    Sprite build_settlement_button = Sprite();
    if (!build_settlement_button.init(120, 90, buttons_path("build_settlement.png")))
    {

        printf("ERROR initializing sprite\n");
    }


    registerButton(build_ship_button, {300.f, screen.y - UI_HEIGHT/2 }, invokeBuildShip);
    registerButton(hire_sailors_button, {300 + 150, screen.y - UI_HEIGHT/2 }, invokeHireSailors);
    registerButton(build_settlement_button, {300 + 150*2, screen.y - UI_HEIGHT/2 }, invokeHireSailors);

    portraitFrame = Sprite();
    if (!portraitFrame.init(150, 150, textures_path("portraitframe.png")))
    {

        printf("ERROR initializing sprite\n");
    }
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
        case GLFW_KEY_W:
            cameraDir.y -= 1;
            break;
        case GLFW_KEY_S:
            cameraDir.y += 1;
            break;
        case GLFW_KEY_A:
            cameraDir.x -= 1;
            break;
        case GLFW_KEY_D:
            cameraDir.x += 1;
            break;
        case GLFW_KEY_Q:
            cameraZoom -= 1;
            break;
        case GLFW_KEY_E:
            cameraZoom += 1;
            break;
        case GLFW_KEY_SPACE:
            world->camera.followSelected=true;
            break;
        default:
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_W:
            cameraDir.y += 1;
            break;
        case GLFW_KEY_S:
            cameraDir.y -= 1;
            break;
        case GLFW_KEY_A:
            cameraDir.x += 1;
            break;
        case GLFW_KEY_D:
            cameraDir.x -= 1;
            break;
        case GLFW_KEY_Q:
            cameraZoom += 1;
            break;
        case GLFW_KEY_E:
            cameraZoom -= 1;
            break;
        case GLFW_KEY_SPACE:
            world->camera.followSelected=false;
            break;
        default:
            break;
        }
    }

    world->camera.move(cameraDir, cameraZoom);
}

void Game::onMouseMove(double xpos, double ypos) {

    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h)
    {
        world->onMouseMove(viewX, viewY);
    }
}

void Game::onScroll(double xoffset, double yoffset) {
    auto zoomVel = static_cast<float>(yoffset / 25);
    world->camera.zoom *= (1 + zoomVel);
    world->camera.boundCameraToWorld();
}
