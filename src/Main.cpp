#include "Common.hpp"
#include "GameWindow.hpp"

#define GL3W_IMPLEMENTATION
#include <gl3w.h>

#include <iostream>
#include <chrono>

#define UPDATE_INTERVAL_MS 1000.f / 60.f

using Clock = std::chrono::high_resolution_clock;

GameWindow window;
Game game;
const int width = 1200;
const int height = 800;

int main()
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
       // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    window.destroy();

    return 0;
}
