#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <unordered_set>
#include <unordered_map>

#include "Common.hpp"
#include "World/World.hpp"
#include <cassert>
#include "Button.hpp"


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
  std::vector<Button> buttons; //TODO: generalize this to UI elements?
  std::unordered_set<Sprite *> selectedSprites; // TODO: these should be gameobjects maybe

  int64_t balance;

  vec2 screen;
};

#endif //DIVCONQ_GAME_H
