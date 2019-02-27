#ifndef DIVCONQ_WINDOW_H
#define DIVCONQ_WINDOW_H

#include "Common.hpp"
#include "Game.hpp"

class GameWindow {
public:
    bool init(vec2 screen, Game* game);

    bool shouldClose();

    void destroy();

    void draw();

private:
    vec2 screen;
    GLFWwindow* window;
    GLuint frameBuffer;

    void onKey(GLFWwindow*, int key, int, int action, int mod);
    void onMouseClick(GLFWwindow* window, int button, int action, int mod);
    void onMouseMove(GLFWwindow* window, double xpos, double ypos);
    void onScroll(GLFWwindow* window, double xoffset, double yoffset);

    Game* game;
};

#endif //DIVCONQ_WINDOW_H
