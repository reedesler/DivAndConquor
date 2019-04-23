#include "Game.hpp"
#include "Common.hpp"
#include "TriSprite.hpp"
#include "Ui/TriangleBtn.h"

#include <iostream>
#include <random>
#include <string>
#define UI_HEIGHT 150

Sprite portraitFrame;
void Game::update()
{
if (world->checkWinCond()){
    state = Game::State::WIN;
}
    switch (state)
    {
    case Game::State::RUNNING:
        if (world->getSelected() != nullptr)
        {
            activeUiElements = unitUis[typeid(*world->getSelected())];
        }
        else if (!activeUiElements.empty())
        {
            activeUiElements = vector<UiElement *>();
        }
        world->update();
        break;
    case Game::State::PAUSE:
        break;
    default:
        break;
    }
}

void Game::draw(const mat3 &projection, int pixelScale)
{
    world->draw(pixelScale);
    drawUI(projection, pixelScale);
}

void Game::drawUI(const mat3 &projection, int pixelScale)
{
    glViewport(0, 0, screen.x * pixelScale, screen.y * pixelScale); // reset viewport

    float sx = 2.0 / screen.x;
    float sy = 2.0 / screen.y;
    for (auto &it : staticUiElements)
    {
        it->Draw(projection);
    }
    for (auto &it : activeUiElements)
    {
        it->Draw(projection);
    }

    // draw selected unit in portrait frame
    if (world->getSelected() != nullptr)
    {
        Sprite spt = world->getSelected()->getSprite();
        bool tmpSelected = spt.selected;
        spt.selected = false;
        spt.state = 0;
        spt.draw(projection, {100, screen.y - UI_HEIGHT / 2.f + 20}, 0.f, {100.f / spt.width, 100.f / spt.height});
        spt.selected = tmpSelected;

        SettlementObject * settl = dynamic_cast<SettlementObject*>(world->getSelected());
        ShipObject * ship  = dynamic_cast<ShipObject*>(world->getSelected());
        if (ship  != nullptr) {
            settl = ship->settlement;
        }

        Sailor* sailor = dynamic_cast<Sailor*>(world->getSelected());
        if (sailor != nullptr) {
            settl = sailor->settlement;
        }
        if (settl != nullptr) {
            auto resources = settl->getResources();
            // swapped around z and y cuz i dont want to redraw icons...
            std::string names[] = {"Gold", "Timber" , "Iron", "Coverage"};
            float vals[] = {resources.x, resources.z, resources.y, world->coverage};
            glm::vec4 black(0.f, 0.f, 0.f, 0.7f);
            tr.config(24, black);
            for(int i =0; i < 4; i++) {
                tr.draw(names[i].c_str() , -1 + 1010 * sx, 1 - (691* sy) - (sy*i*30), sx, sy);
                auto val = std::to_string((int)vals[i]);
                if(i == 3)
                    val += "%";
                tr.draw(val.c_str(), -1 + 1125 * sx, 1 - (691* sy) - (sy*i*30), sx, sy);
            }	
        }
    }



        int y_offset = -1;
        for (auto line : logLines) {
            std::string text = line.first;
            long time = line.second;
            long now = currentTimeMs();
            long delta = now - time;
            // 2 seconds display time, then 2 seconds fade
            float bright = 2.f - (delta / 2000.f);
            if (bright <= 0.f)
                break;
            glm::vec4 black(0.f, 0.f, 0.f, bright);
            tr.config(24, black);
            tr.draw( text.c_str() , -1 + 51 * sx, 1 - (151* sy) - (sy*y_offset*30), sx, sy);
            glm::vec4 white(1.f, 1.f, 1.f, bright);
            tr.config(24, white);
            tr.draw( text.c_str() , -1 + 50 * sx, 1 - (150* sy) - (sy*y_offset*30), sx, sy);
            y_offset --;
        }
    if (state == Game::State::PAUSE)
    {

        // TODO: dim screen
        for (auto &it : pauseScreenUiElements)
        {
            it->Draw(projection);
        }

    float sx = 2.0 / screen.x;
    float sy = 2.0 / screen.y;


    glm::vec4 translucent_black(1.f, 1.f, 1.f, 1.f);
    int line_spacing = 27;
    tr.config(24, translucent_black);

    std::vector<std::string> lines = {
        "Welcome to Divide and Conquer!",
        "The objective is to conquer more than 80% of the map by building settlements, while fending off pirates!", // TODO: IS THIS TRUE???
        "Your sailors (deployed at a settlement) can collect resources, but you'll need ships to travel across water.",
        "In lieu of a treasury, each settlement has its own inventory of resources, shared with its associated units.",
        "",
        "== Camera ==",
        "  WASD or edge-pan - move camera.",
        "  Q/E or scroll - zoom.",
        "  Hold space - follow main selected unit.",
        "== Gameplay ==",
        "  Left-drag - select units.",
        "  Right-click - move/attack.",
        "  Tab - switch which unit in the selection is the main one.",
        "  Escape - deselect all non-main units.",
        "  1, 2 - Use unit abilities.",
        "",
        "Click anywhere to dismiss this screen. Good luck!",
        };
        int y_offset = 1;
        for (auto line : lines) {
            tr.draw( line.c_str() , -1 + 50 * sx, 1 - (20* sy) - (sy*y_offset*line_spacing), sx, sy);
            y_offset ++;
        }
    }

    if(state == Game::State::WIN){
        for (auto &it : pauseScreenUiElements)
        {
            it->Draw(projection);
        }

        float sx = 2.0 / screen.x;
        float sy = 2.0 / screen.y;


        glm::vec4 translucent_black(1.f, 1.f, 1.f, 1.f);
        tr.config(120, translucent_black);

        std::vector<std::string> lines = {
                "         ",
                "         ",
                "         ",
                "         ",
                "         ",
                "         ",
                "         ",
                "         ",
                "YOU ARE VICTORIOUS",
        };
        int y_offset = 1;
        for (auto line : lines) {
            tr.draw( line.c_str() , -1 + 50 * sx, 1 - (20* sy) - (sy*y_offset*30), sx, sy);
            y_offset ++;
        }
    }



}

void invokeBuildShip(Game *game, int button, int action, double xpos, double ypos)
{
    game->world->addShip();
}

void invokeBuildSettlement(Game *game, int button, int action, double xpos, double ypos)
{
    game->world->addSettlement();
}
void invokeHireSailors(Game *game, int button, int action, double xpos, double ypos)
{
    game->world->addSailor();

}
void invokeTogPause(Game *game, int btn, int action, double xpos, double ypos)
{
    if (game->state == Game::State::PAUSE)
        game->state = Game::State::RUNNING;
    else
        game->state = Game::State::PAUSE;
}
void Game::init(vec2 screen)
{
    std::srand(1); // fixed seed to make sure resource distirbution makes for a winnable game :D
    this->screen = screen;
    this->state = Game::State::PAUSE;

    prevMouseXpos = screen.x / 2.f;
    prevMouseYpos = screen.y / 2.f;

    world = new World(this, {0, UI_HEIGHT, (GLint)screen.x, (GLint)screen.y - UI_HEIGHT});

    tr.init(fonts_path("Carlito-Bold.ttf"));
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

    unitUis[typeid(Sailor)].push_back(new Button(build_settlement_button, {300.f, screen.y - UI_HEIGHT / 2}, invokeBuildSettlement));
    unitUis[typeid(ShipObject)].push_back(new Button(build_settlement_button, {300.f, screen.y - UI_HEIGHT / 2}, invokeBuildSettlement));

    unitUis[typeid(SettlementObject)].push_back(new Button(build_ship_button, {300.f, screen.y - UI_HEIGHT / 2}, invokeBuildShip));
    unitUis[typeid(SettlementObject)].push_back(new Button(hire_sailors_button, {300 + 150, screen.y - UI_HEIGHT / 2}, invokeHireSailors));

    Sprite bottombar = Sprite();
    if (!bottombar.init(screen.x, UI_HEIGHT, textures_path("bottombar.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    staticUiElements.push_back(new UiElement(bottombar, {screen.x / 2, screen.y - UI_HEIGHT / 2}, nullptr));

    TriSprite pause_btn = TriSprite();
    if (!pause_btn.init(75, 60, textures_path("pause_btn.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    staticUiElements.push_back(new TriangleBtn(pause_btn, {screen.x * 0.8f, screen.y - UI_HEIGHT / 2}, invokeTogPause));
    Sprite paused_icon = Sprite();
    if (!paused_icon.init(screen.x, screen.y, textures_path("paused.png")))
    {
        printf("ERROR initializing sprite\n");
    }
    pauseScreenUiElements.push_back(new UiElement(paused_icon, {screen.x / 2, screen.y / 2}, invokeTogPause));
    pauseScreenUiElements.push_back(new Label("=PAUSED=", 48, {1, 1}));
    //auto characters = loadFont("data/fonts/Carlito-Bold.ttf");

    //renderText(characters, "std::string", vec2{20.f, 20.f}, 1.0, vec3{0.f, 200.f, 0.f});
    //renderText(characters, "This is sample text", vec2{25.0f, 25.0f}, 1.0f, vec3{0.5, 0.8f, 0.2f});


    world->update();
}

bool Game::registerButton(Sprite &btn, vec2 location, UiCallback::OnClickFunc callback)
{
    activeUiElements.push_back(new Button{btn, location, callback});
    return true;
}

void Game::onClick(int button, int action, double xpos, double ypos)
{
    //printf("falled in the region? %lf %lf\n", xpos, ypos);
    if (action == GLFW_PRESS)
    {
        if (state == State::PAUSE)
            for (auto &it : pauseScreenUiElements)
            {
                if (it->InBounds({(float)xpos, (float)ypos}))
                {
                    it->OnClick(this, 0, xpos, ypos);
                    return; // prevent clickthrough
                }
            }
        else
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
            for (size_t i = staticUiElements.size(); i--;)
            {
                auto *it = staticUiElements[i];
                if (it->InBounds({(float)xpos, (float)ypos}))
                {
                    it->OnClick(this, 0, xpos, ypos);
                    return; // prevent clickthrough
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
        case GLFW_KEY_1:
            if(world->getSelected() != nullptr) {
                auto v = unitUis[typeid(*world->getSelected())];
                if(v.size() > 0)
                    v.at(0)->OnClick(this,0,0,0);
            }
            break;
        case GLFW_KEY_2:
            if(world->getSelected() != nullptr) {
                auto v = unitUis[typeid(*world->getSelected())];
                if(v.size() > 1)
                    v.at(1)->OnClick(this,0,0,0);
            }
            break;
        case GLFW_KEY_P:
            this->printLn("Test P!");
            break;
        case GLFW_KEY_M:
            this->printLn("Test M!");
            break;
        case GLFW_KEY_SPACE:
            world->camera.followSelected = true;
            break;
        case GLFW_KEY_TAB:
        {
            if( world->selectedObjects.size() <= 1){
                break;
            }
            auto it = std::find(world->selectedObjects.begin(), world->selectedObjects.end(), world->selectedObject);
            if (world->selectedObject == nullptr || it == world->selectedObjects.end())
            {
                world->selectedObject = world->selectedObjects.at(0);
            } else {
                long unsigned int index = std::distance(world->selectedObjects.begin(), it);
                index ++;
                if (index >= world->selectedObjects.size()){
                    index = 0;
                }
                world->selectedObject = world->selectedObjects.at(index);
            }
            break;
        }
        case GLFW_KEY_ESCAPE: // TODO: or do we want this to open the menu?
        {
            if(world->selectedObject == nullptr || world->selectedObjects.size() <= 1){
                break;
            }
            world->selectedObjects = {world->selectedObject};
            break;
        }
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
            world->camera.followSelected = false;
            break;
        default:
            break;
        }
    }

    world->camera.move(cameraDir, cameraZoom);
}

#define MOUSE_MOVE_SIZE 40

void Game::onMouseMove(double xpos, double ypos)
{

    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h)
    {
        world->onMouseMove(viewX, viewY);
    }

    if (xpos < 0 || xpos > screen.x || ypos < 0 || ypos > screen.y)
    {
        xpos = screen.x / 2.f;
        ypos = screen.y / 2.f;
    }
    vec2 cameraDir = {0, 0};
    if (xpos <= MOUSE_MOVE_SIZE && prevMouseXpos > MOUSE_MOVE_SIZE)
        cameraDir.x -= 1;
    if (prevMouseXpos <= MOUSE_MOVE_SIZE && xpos > MOUSE_MOVE_SIZE)
        cameraDir.x += 1;

    if (xpos >= screen.x - MOUSE_MOVE_SIZE && prevMouseXpos < screen.x - MOUSE_MOVE_SIZE)
        cameraDir.x += 1;
    if (prevMouseXpos >= screen.x - MOUSE_MOVE_SIZE && xpos < screen.x - MOUSE_MOVE_SIZE)
        cameraDir.x -= 1;

    if (ypos <= MOUSE_MOVE_SIZE && prevMouseYpos > MOUSE_MOVE_SIZE)
        cameraDir.y -= 1;
    if (prevMouseYpos <= MOUSE_MOVE_SIZE && ypos > MOUSE_MOVE_SIZE)
        cameraDir.y += 1;

    if (ypos >= screen.y - MOUSE_MOVE_SIZE && prevMouseYpos < screen.y - MOUSE_MOVE_SIZE)
        cameraDir.y += 1;
    if (prevMouseYpos >= screen.y - MOUSE_MOVE_SIZE && ypos < screen.y - MOUSE_MOVE_SIZE)
        cameraDir.y -= 1;

    world->camera.move(cameraDir, 0);

    prevMouseXpos = xpos;
    prevMouseYpos = ypos;


}

void Game::onScroll(double xoffset, double yoffset, double xpos, double ypos)
{
    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h)
    {
        auto zoomVel = static_cast<float>(yoffset / 25);
        world->camera.zoomToPoint(1 + zoomVel, {viewX, viewY});
    }
}
