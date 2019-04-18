#include "Common.hpp"
#include "GameWindow.hpp"
#include "TextRenderer.hpp"
#include "Ui/Polygon.hpp"

#define GL3W_IMPLEMENTATION
#include <gl3w.h>

#include <iostream>
#include <chrono>

#define UPDATE_INTERVAL_MS 1000.f / 60.f

using Clock = std::chrono::high_resolution_clock;

#include <glm/ext.hpp>

GameWindow window;
Game game;
const int width = 1200;
const int height = 800;

void _check_gl_error(const char *file, int line)
{
    GLenum err(glGetError());

    while (err != GL_NO_ERROR)
    {
        string error;

        switch (err)
        {
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }

        cerr << "GL_" << error.c_str() << " - " << file << ":" << line << endl;
        err = glGetError();
    }
}

void displayText(double window_width, double window_height)
{
    TextRenderer tr;
    tr.init(fonts_path("Carlito-Bold.ttf"));

    float sx = 2.0 / window_width;
    float sy = 2.0 / window_height;

    _check_gl_error(__FILE__, __LINE__);

    /* Set font size to 48 pixels, color to black */
    glm::vec4 translucent_black(0, 0, 0, 0.5);
    tr.config(48, translucent_black);

    /* Effects of alignment */
    tr.draw("Fake button text", -1 + 8 * sx, 1 - 50 * sy, sx, sy);
}

void displayPolygon()
{
    Polygon polygon;
    float vertices[] = {
        0.0, 0.0, 0.0, 0.0, 1.0,
        -0.273529225, 0.2826445, 0.0, 0.0, 1.0,
        -0.109408175, 0.40117325, 0.0, 0.0, 1.0,
        0.091170575, 0.2005875, 0.0, 0.0, 1.0,
        0.237054, 0.19146875, 0.0, 0.0, 1.0,
        0.036475225, 0.528819, 0.0, 0.0, 1.0,
        0.145883425, 0.018235, 0.0, 0.0, 1.0,
        -0.00911, 0.05470575, 0.0, 0.0, 1.0,
        0.18235875, -0.1094115, 0.0, 0.0, 1.0,
        0.13675575, -0.3464675, 0.0, 0.0, 1.0,
        0.10942575, -0.136763, 0.0, 0.0, 1.0,
        0.33733475, -0.26441025, 0.0, 0.0, 1.0,
        0.091188, -0.054706, 0.0, 0.0, 1.0,
        0.0182375, -0.11852875, 0.0, 0.0, 1.0,
        0.87528325, -0.33735025, 0.0, 0.0, 1.0};
    unsigned int elements[] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 7,
        0, 7, 8,
        0, 8, 9,
        0, 9, 10,
        0, 10, 11,
        0, 11, 12,
        0, 12, 13,
        0, 13, 14,
        0, 14, 15,
        0, 15, 16};
//    polygon.init(vertices, sizeof(vertices), elements, sizeof(elements), shader_path("simple.vs.glsl"), shader_path("simple.fs.glsl"));
  //  polygon.render();
    _check_gl_error(__FILE__, __LINE__);
}

int main(void)
{
    if (!window.init({(float)width, (float)height}, &game))
    {
        // Time to read the error message
        std::cout << "Press any key to exit" << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }

    auto lastUpdate = Clock::now();

    while (!window.shouldClose())
    {
        glfwPollEvents();

        auto now = Clock::now();
        auto updateDebt =
            (float)(std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate)).count() / 1000;
        if (updateDebt > 10 * UPDATE_INTERVAL_MS)
            updateDebt = 10 * UPDATE_INTERVAL_MS;
        while (updateDebt >= UPDATE_INTERVAL_MS)
        {
            game.update();
            updateDebt -= UPDATE_INTERVAL_MS;
            lastUpdate = now;
        }

        window.draw();

        displayText(width, height);
        displayPolygon();
        glfwSwapBuffers(window.window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    window.destroy();

    return 0;
}
