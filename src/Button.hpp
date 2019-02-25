#ifndef DIVCONQ_BUTTON_H
#define DIVCONQ_BUTTON_H

#include "Sprite.hpp"
#include "Common.hpp"
#include "World/GameObject.hpp"
#include <chrono>

class Game;

// ButtonOnClickFunc has a parameter list of {Game *game, int button, int action, double xpos, double ypos}
typedef void (*ButtonOnClickFunc)(Game *, int, int, double, double);

class Button
{
  public:
    // Button::OnClickFunc has a parameter list of {Game *game, int button, int action, double xpos, double ypos}
    typedef void (*OnClickFunc)(Game *, int, int, double, double);

  private:
    Button::OnClickFunc callback;
    long lastPressMs;
    vec2 pos;

  public:
    Sprite sprite;
    Button(Sprite &btn, vec2 location, Button::OnClickFunc callback);
    void OnClick(Game *game, int action, double xpos, double ypos);
    void Draw(const mat3 &projection);
    bool InBounds(vec2 point);
    ~Button();
};

#endif //DIVCONQ_BUTTON_H