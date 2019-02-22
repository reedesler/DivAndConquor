#ifndef DIVCONQ_GAME_H
#define DIVCONQ_GAME_H

#include <vector>
#include <unordered_map>

#include "Common.hpp"
#include "World/World.hpp"

typedef void (*ButtonOnClickFunc)(int, int, double, double);

class Game
{
public:
  void init(vec2 screen);
  void update();
  void draw(const mat3 &projection, int pixelScale);
  void onKey(int key, int scancode, int action);
  bool registerButton(Sprite btn, vec2 location, ButtonOnClickFunc callback);
  bool removeButton(Sprite btn);
  void onClick(int button, int action, double xpos, double ypos);

private:
  World *world;
  std::unordered_map<Sprite *, vec2> buttonPositions;
  std::unordered_map<Sprite *, ButtonOnClickFunc> buttonCallbacks;
  std::vector<Sprite *> selectedSprites;
};

#endif //DIVCONQ_GAME_H
