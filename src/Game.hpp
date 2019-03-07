#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <unordered_set>
#include <unordered_map>

#include "Common.hpp"
#include "World/World.hpp"
#include <cassert>
#include <typeindex>
#include "Ui/Button.hpp"
#include "Ui/UiCallback.h"

struct Settlement {
    uint16_t gold;
    uint16_t timber;
    uint16_t iron;
    vec2 location;
    uint16_t influence;
};

struct Ship {
    uint16_t capacity;
    uint16_t sailingDistance;
    uint16_t sailors;
    uint16_t maxSpeed;
    uint16_t price;
    uint16_t firearm;
};

static const Ship proa = {10, 10, 2, 4, 100, 0},
        catboat = {15, 15, 2, 6, 200, 0},
        sloop = {30, 30, 4, 10, 400, 1},
        cutter = {30, 30, 4, 10, 800, 1},
        yawl = {30, 30, 4, 10, 1600, 1},
        ketch = {30, 30, 4, 10, 3200, 1},
        schooner = {30, 30, 4, 10, 6400, 1},
        topsailSchooner = {30, 30, 4, 10, 12800, 1},
        brig = {30, 30, 4, 10, 25600, 1},
        brigantine = {30, 30, 4, 10, 25600, 1},
        barquentine = {30, 30, 4, 10, 25600, 1},
        barque = {30, 30, 4, 10, 25600, 1},
        fullyRiggedShip = {30, 30, 4, 10, 25600, 1};

// type forwarding since we have circular includes
class Button;

class Game {
public:
    void init(vec2 screen);
    void update();
    void draw(const mat3 &projection, int pixelScale);
    void onKey(int key, int scancode, int action);
    bool registerButton(Sprite &btn, vec2 location, UiCallback::OnClickFunc onclick);
    // bool removeButton(Sprite *btn);
    void onClick(int button, int action, double xpos, double ypos);
    void onMouseMove(double xpos, double ypos);
    void onScroll(double xoffset, double yoffset, double xpos, double ypos);
    void buildShip(vec2 location);
    World* world;
private:

    std::map<std::type_index, std::vector<UiElement*>> unitUis;
    std::vector<UiElement*> activeUiElements;
    std::vector<UiElement*> staticUiElements;
    std::unordered_set<Sprite*> selectedSprites; // TODO: these should be gameobjects maybe

    vec2 screen;

    void drawUI(const mat3 &projection, int pixelScale);
};

#endif //DIVCONQ_GAME_H
