#include "GameWindow.hpp"
#include <iostream>

namespace
{
namespace
{
void glfw_err_cb(int error, const char *desc)
{
    fprintf(stderr, "%d: %s", error, desc);
}
} // namespace
} // namespace

bool GameWindow::init(vec2 screen, Game *game)
{
    this->screen = screen;
    this->game = game;

    //-------------------------------------------------------------------------
    // GLFW / OGL Initialization
    // Core Opengl 3.
    glfwSetErrorCallback(glfw_err_cb);
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow((int)screen.x, (int)screen.y, "Divide and Conquer", nullptr, nullptr);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to initialize window");
        return false;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // vsync

    // Load OpenGL function pointers
    gl3w_init();

    glfwSetWindowUserPointer(window, this);
    auto key_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2, int _3) {
        ((GameWindow *)glfwGetWindowUserPointer(wnd))->onKey(wnd, _0, _1, _2, _3);
    };
    auto scroll_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((GameWindow *)glfwGetWindowUserPointer(wnd))->onScroll(wnd, _0, _1);
    };
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((GameWindow *)glfwGetWindowUserPointer(wnd))->onMouseMove(wnd, _0, _1);
    };
    auto mouse_click_redirect = [](GLFWwindow *wnd, int _0, int _1, int _2) {
        ((GameWindow *)glfwGetWindowUserPointer(wnd))->onMouseClick(wnd, _0, _1, _2);
    };
    glfwSetKeyCallback(window, key_redirect);
    glfwSetCursorPosCallback(window, cursor_pos_redirect);
    glfwSetMouseButtonCallback(window, mouse_click_redirect);
    glfwSetScrollCallback(window, scroll_redirect);

    // Create a frame buffer
    frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    game->init(screen);

    return true;
}

void _check_gl_error(const char *file, int line);

void GameWindow::draw()
{
    // Clearing error buffer
    gl_flush_errors();

    // Getting size of window
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    /* Enable blending, necessary for alpha texture */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Clearing backbuffer
    glViewport(0, 0, w, h);
    glDepthRange(0.00001, 10);
    const float clear_color[3] = {0.f,0.f,0.f};//{0.7f, 0.7f, 0.8f};
    glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0);
    glClearDepth(1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Fake projection matrix, scales with respect to window coordinates
    // PS: 1.f / w in [1][1] is correct.. do you know why ? (:
    float left = 0.f;        // *-0.5;
    float top = 0.f;         // (float)h * -0.5;
    float right = screen.x;  // *0.5;
    float bottom = screen.y; // *0.5;

    float sx = 2.f / (right - left);
    float sy = 2.f / (top - bottom);
    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    mat3 projection_2D{{sx, 0.f, 0.f},
                       {0.f, sy, 0.f},
                       {tx, ty, 1.f}};

    game->draw(projection_2D, static_cast<int>(w / screen.x));

    // Presenting
    //glfwSwapBuffers(window);
}

bool GameWindow::shouldClose()
{
    return static_cast<bool>(glfwWindowShouldClose(window));
}

void GameWindow::destroy()
{
    glDeleteFramebuffers(1, &frameBuffer);
    glfwDestroyWindow(window);
}

void GameWindow::onKey(GLFWwindow *, int key, int scancode, int action, int mod)
{
    game->onKey(key, scancode, action);
}

void GameWindow::onMouseMove(GLFWwindow *window, double xpos, double ypos)
{
    game->onMouseMove(xpos, ypos);
}

void GameWindow::onMouseClick(GLFWwindow *window, int button, int action, int mod)
{
    double xpos = 0.0, ypos = 0.0;
    glfwGetCursorPos(window, &xpos, &ypos);
    game->onClick(button, action, xpos, ypos);
}

<<<<<<< HEAD
void GameWindow::onScroll(GLFWwindow *window, double xoffset, double yoffset)
{
    game->onScroll(xoffset, yoffset);
=======
void GameWindow::onScroll(GLFWwindow* window, double xoffset, double yoffset) {
    double xpos = 0.0, ypos = 0.0;
    glfwGetCursorPos(window, &xpos, &ypos);
    game->onScroll(xoffset, yoffset, xpos, ypos);
>>>>>>> 2dfce07e57dec087c7e30919a3e47291b2091e26
}