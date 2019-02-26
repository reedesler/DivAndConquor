#include "Game.hpp"
#include "Common.hpp"

#include <iostream>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

struct vec2ui
{
    uint32_t x, y;
};

struct vec2i
{
    int32_t x, y;
};

/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    GLuint TextureID; // ID handle of the glyph texture
    vec2ui Size;      // Size of glyph
    vec2i Bearing;    // Offset from baseline to left/top of glyph
    long Advance;     // Horizontal offset to advance to next glyph
};

GLuint VAO, VBO;

void renderText(std::map<GLchar, Character> characters, std::string text, vec2 location, GLfloat scale, vec3 color)
{
    Effect effect;
    // Activate corresponding render state
    effect.load_from_file(shader_path("label.vs.glsl"), shader_path("label.fs.glsl"));
    glUseProgram(effect.program);
    glUniform3f(glGetUniformLocation(effect.program, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        GLfloat xpos = location.x + ch.Bearing.x * scale;
        GLfloat ypos = location.y - (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 0.0},
            {xpos, ypos, 0.0, 1.0},
            {xpos + w, ypos, 1.0, 1.0},

            {xpos, ypos + h, 0.0, 0.0},
            {xpos + w, ypos, 1.0, 1.0},
            {xpos + w, ypos + h, 1.0, 0.0}};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        location.x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
        printf("%f\n", location.x);
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::update(float time)
{
    world->update(time);
}

void Game::draw(const mat3 &projection, int pixelScale)
{
    world->draw(pixelScale);
    glViewport(0, 0, screen.x, screen.y); // reset viewport
    // buttons probably shouldnt have their own viewport
    // after all, what if we want alert boxes or some menu that involves buttons over the world
    for (auto &it : buttons)
    {
        it.Draw(projection);
    }
}

void invokeBuildShip(Game *game, int button, int action, double xpos, double ypos)
{
    printf("invokeBuildShip! \n");
    game->buildShip();
}

void invokeHireSailors(Game *game, int button, int action, double xpos, double ypos)
{
    printf("hireSailors!\n");
    //    mat3 pos = {{1.f, 0.f, (float)xpos},
    //                {0.f, 1.f, (float)ypos},
    //                {0.f,0.f,1.f}};
    //    p.draw(pos);
}

void invokeSubmitJourney(int button, int action, double xpos, double ypos)
{
    printf("Starting a journey from a to b!\n");
    // find the two selected settlements that represent the src and dst
}

void Game::buildShip()
{
    this->balance -= 500;
    printf("balance %d\n", balance);
    this->fleet.insert(new Ship(proa));
}

void Game::init(vec2 screen)
{
    this->screen = screen;

    world = new World({0, 200, (GLint)screen.x, (GLint)screen.y - 200});

    Sprite build_ship_button = Sprite();
    if (!build_ship_button.init(120, 90, buttons_path("build_ship.png")))
    {
        printf("ERROR initializing sprite\n");
    }

    Sprite hire_sailors_button = Sprite();
    if (!hire_sailors_button.init(120, 90, buttons_path("hire_sailors.png")))
    {

        printf("ERROR initializing sprite\n");
    }

    balance = 5000;

    registerButton(build_ship_button, {80.f, 100.f}, invokeBuildShip);
    registerButton(hire_sailors_button, {80.f, 500.f}, invokeHireSailors);
}

bool Game::registerButton(Sprite &btn, vec2 location, Button::OnClickFunc callback)
{
    buttons.emplace_back(btn, location, callback);
    return true;
}

// TODO: this doesn't seem to account for viewport size... y positions seem a bit off
void Game::onClick(int button, int action, double xpos, double ypos)
{
    //printf("falled in the region? %lf %lf\n", xpos, ypos);
    if (action == GLFW_PRESS)
    {
        for (auto &it : buttons)
        {

            if (it.InBounds({(float)xpos, (float)ypos}))
            {
                it.OnClick(this, 0, xpos, ypos);
                if (selectedSprites.find(&it.sprite) == selectedSprites.end())
                {
                    selectedSprites.insert(&it.sprite);
                }
                else
                {
                    selectedSprites.erase(&it.sprite);
                }
            }
        }
    } /* else if (action == GLFW_RELEASE) {

    }*/

    rect viewPort = world->camera.viewPort;
    auto viewX = static_cast<float>(xpos - viewPort.x);
    auto viewY = static_cast<float>(ypos - screen.y + viewPort.y + viewPort.h);
    if (viewX >= 0 && viewX <= viewPort.w && viewY >= 0 && viewY <= viewPort.h)
    {
        world->onClick(button, action, viewX, viewY);
    }
}

void Game::onKey(int key, int scancode, int action)
{
    vec2 cameraDir = {0, 0};
    int cameraZoom = 0;
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            cameraDir.y -= 1;
            break;
        case GLFW_KEY_DOWN:
            cameraDir.y += 1;
            break;
        case GLFW_KEY_LEFT:
            cameraDir.x -= 1;
            break;
        case GLFW_KEY_RIGHT:
            cameraDir.x += 1;
            break;
        case GLFW_KEY_COMMA:
            cameraZoom -= 1;
            break;
        case GLFW_KEY_PERIOD:
            cameraZoom += 1;
            break;
        case GLFW_KEY_W:
            world->pirate.moveUp = true;
            break;
        case GLFW_KEY_S:
            world->pirate.moveDown = true;
            break;
        case GLFW_KEY_A:
            world->pirate.moveLeft = true;
            break;
        case GLFW_KEY_D:
            world->pirate.moveRight = true;
            break;
        default:
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            cameraDir.y += 1;
            break;
        case GLFW_KEY_DOWN:
            cameraDir.y -= 1;
            break;
        case GLFW_KEY_LEFT:
            cameraDir.x += 1;
            break;
        case GLFW_KEY_RIGHT:
            cameraDir.x -= 1;
            break;
        case GLFW_KEY_COMMA:
            cameraZoom += 1;
            break;
        case GLFW_KEY_PERIOD:
            cameraZoom -= 1;
            break;
        case GLFW_KEY_W:
            world->pirate.moveUp = false;
            break;
        case GLFW_KEY_S:
            world->pirate.moveDown = false;
            break;
        case GLFW_KEY_A:
            world->pirate.moveLeft = false;
            break;
        case GLFW_KEY_D:
            world->pirate.moveRight = false;
            break;
        default:
            break;
        }
    }

    world->camera.move(cameraDir, cameraZoom);
}