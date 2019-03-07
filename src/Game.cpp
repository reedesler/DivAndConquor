#include "Game.hpp"
#include "Common.hpp"

#include <iostream>
#include <string>
#define  UI_HEIGHT 150

Sprite portraitFrame;
void Game::update()
{
    if(world->getSelected() != nullptr) {
        activeUiElements = unitUis[typeid(*world->getSelected())];
    }
    else if (!activeUiElements.empty()) {
        activeUiElements = vector<UiElement *>();
    }
    world->update();
}

void Game::draw(const mat3 &projection, int pixelScale)
{
    world->draw(pixelScale);
    drawUI(projection, pixelScale);
}

void Game::drawUI(const mat3 &projection, int pixelScale) {
    glViewport(0, 0, screen.x * pixelScale, screen.y * pixelScale); // reset viewport

    for (auto &it : staticUiElements)
    {
        it->Draw(projection);
    }
    for (auto &it : activeUiElements)
    {
        it->Draw(projection);
    }

    // draw selected unit in portrait frame
    if(world->getSelected() != nullptr){
        Sprite spt =  world->getSelected()->getSprite();
        spt.tint = {1.f,1.f,1.f};
        spt.state = 0;
        spt.draw(projection,{100, screen.y - UI_HEIGHT/2.f + 20 } , 0.f, {100.f/ spt.width, 100.f/spt.height});
    }
}

void invokeBuildShip(Game *game, int button, int action, double xpos, double ypos)
{
    printf("invokeBuildShip! \n");

    game->buildShip(vec2{(float)xpos, (float)ypos});
}

void invokeBuildSettlement(Game *game, int button, int action, double xpos, double ypos)
{
    printf("buildSettlement!\n");
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

    world = new World({0, UI_HEIGHT, (GLint)screen.x, (GLint)screen.y - UI_HEIGHT});

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


    unitUis[typeid(ShipObject)].push_back(new Button(build_settlement_button, {300.f, screen.y - UI_HEIGHT/2 }, invokeBuildSettlement));

    unitUis[typeid(SettlementObject)].push_back(new Button(build_ship_button, {300.f, screen.y - UI_HEIGHT/2 }, invokeBuildShip));
    unitUis[typeid(SettlementObject)].push_back(new Button(hire_sailors_button, {300 + 150, screen.y - UI_HEIGHT/2 }, invokeHireSailors));




    Sprite bottombar = Sprite();
    if (!bottombar.init(screen.x, UI_HEIGHT, textures_path("bottombar.png")))
    {

        printf("ERROR initializing sprite\n");
    }
    staticUiElements.push_back(new UiElement(bottombar, {screen.x/2, screen.y - UI_HEIGHT/2}, nullptr));

    //auto characters = loadFont("data/fonts/Carlito-Bold.ttf");

    //renderText(characters, "std::string", vec2{20.f, 20.f}, 1.0, vec3{0.f, 200.f, 0.f});
    //renderText(characters, "This is sample text", vec2{25.0f, 25.0f}, 1.0f, vec3{0.5, 0.8f, 0.2f});

    //==================================
    // sound initialized here

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "Failed to initialize SDL Audio");
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        fprintf(stderr, "Failed to open audio device");
    }

    background_music = Mix_LoadMUS(audio_path("background.wav"));


    if (background_music == nullptr)
    {
        fprintf(stderr, "Failed to load sounds\n %s\n %s\n %s\n make sure the data directory is present",
                audio_path("music.wav"),
                audio_path("salmon_dead.wav"),
                audio_path("salmon_eat.wav"));

    }

    // Playing background music undefinitely
    Mix_PlayMusic(background_music, -1);

    fprintf(stderr, "Loaded music\n");

}

bool Game::registerButton(Sprite &btn, vec2 location, UiCallback::OnClickFunc callback)
{
    activeUiElements.push_back(new Button{btn, location, callback});
    return true;
}

// TODO: this doesn't seem to account for viewport size... y positions seem a bit off
void Game::onClick(int button, int action, double xpos, double ypos)
{
    //printf("falled in the region? %lf %lf\n", xpos, ypos);
    if (action == GLFW_PRESS)
    {
        for (auto &it : activeUiElements)
        {

            if (it->InBounds({(float)xpos, (float)ypos}))
            {
                it->OnClick(this, 0, xpos, ypos);
                if (selectedSprites.find(&it->sprite) == selectedSprites.end())
                {
                    selectedSprites.insert(&it->sprite);
                }
                else
                {
                    selectedSprites.erase(&it->sprite);
                }
                return; // prevent clickthrough
            }
        }
        for (auto &it : staticUiElements)
        {

            if (it->InBounds({(float)xpos, (float)ypos}))
            {
                it->OnClick(this, 0, xpos, ypos);
                return; // prevent clickthrough
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
    } else {
        world->onMouseMove(-1, -1);
    }
}

void Game::onScroll(double xoffset, double yoffset, double xpos, double ypos) {
    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h) {
        auto zoomVel = static_cast<float>(yoffset / 25);
        world->camera.zoomToPoint(1 + zoomVel, {viewX, viewY});
    }
}
