#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <unordered_set>
#include <unordered_map>

#include "Common.hpp"
#include "World/World.hpp"
#include <cassert>
#include "Button.hpp"

struct Settlement
{
  uint16_t gold;
  uint16_t timber;
  uint16_t iron;
  vec2 location;
  uint16_t influence;
};

struct Ship
{
  uint16_t capacity, maxWeight;
  uint16_t sailors;
  uint16_t maxSpeed;
  uint16_t firearm;
};

struct Journey
{
  Settlement src, dst;
  Ship vessel;
  uint16_t gold;
  uint16_t timber;
  uint16_t iron;
  float progress; // from 0.f to 100.f, we should be able to determine the location of the ship based on this
};

class Game
{
public:
  void init(vec2 screen);
  void update();
  void draw(const mat3 &projection, int pixelScale);
  void onKey(int key, int scancode, int action);
  bool registerButton(Sprite &btn, vec2 location, Button::OnClickFunc callback);
  // bool removeButton(Sprite *btn);
  void onClick(int button, int action, double xpos, double ypos);

private:
  World *world;
  std::vector<Button> buttons;                  //TODO: generalize this to UI elements?
  std::unordered_set<Sprite *> selectedSprites; // TODO: these should be gameobjects maybe

  int64_t balance;
  uint64_t sailors;
  std::unordered_set<Journey> sailingShips;
  vec2 screen;
};

#endif //DIVCONQ_GAME_H
