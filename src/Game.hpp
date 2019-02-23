#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <unordered_set>
#include <unordered_map>

#include "Common.hpp"
#include "World/World.hpp"

// ButtonOnClickFunc has a parameter list of {int button, int action, double xpos, double ypos}
typedef void (*ButtonOnClickFunc)(int, int, double, double);

class Game
{
public:
  void init(vec2 screen);
  void update();
  void draw(const mat3 &projection, int pixelScale);
  void onKey(int key, int scancode, int action);
  bool registerButton(Sprite *btn, vec2 location, ButtonOnClickFunc callback);
  bool removeButton(Sprite *btn);
  void onClick(int button, int action, double xpos, double ypos);

private:
  World *world;
  std::unordered_map<Sprite *, vec2> buttonPositions;
  std::unordered_map<Sprite *, ButtonOnClickFunc> buttonCallbacks;
  std::unordered_set<Sprite *> selectedSprites;

  int64_t balance;

  vec2 screen;
};

#endif //DIVCONQ_GAME_H
