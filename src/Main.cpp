#include "Common.hpp"
#include "GameWindow.hpp"
#include "TextRenderer.hpp"

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
    tr.draw("Test String", -1 + 8 * sx, 1 - 50 * sy, sx, sy);
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
        while (updateDebt >= UPDATE_INTERVAL_MS)
        {
            game.update();
            updateDebt -= UPDATE_INTERVAL_MS;
            lastUpdate = now;
        }

        window.draw();

        displayText(width, height);
        glfwSwapBuffers(window.window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    window.destroy();

    return 0;
}
