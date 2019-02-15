#include "GameWindow.hpp"
#include "Game.hpp"

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
    auto cursor_pos_redirect = [](GLFWwindow *wnd, double _0, double _1) {
        ((GameWindow *)glfwGetWindowUserPointer(wnd))->onMouseMove(wnd, _0, _1);
    };
    glfwSetKeyCallback(window, key_redirect);
    glfwSetCursorPosCallback(window, cursor_pos_redirect);

    // Create a frame buffer
    frameBuffer = 0;
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

    return true;
}

void GameWindow::draw()
{
    // Clearing error buffer
    gl_flush_errors();

    // Getting size of window
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Clearing backbuffer
    glViewport(0, 0, w, h);
    glDepthRange(0.00001, 10);
    const float clear_color[3] = {1.f, 1.f, 1.f};
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
    mat3 projection_2D{{sx, 0.f, 0.f}, {0.f, sy, 0.f}, {tx, ty, 1.f}};

    game->draw(projection_2D);

    // Presenting
    glfwSwapBuffers(window);
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
}
