#include "Game.hpp"
#include "Common.hpp"

#include <iostream>
#include <string>

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

    //auto characters = loadFont("data/fonts/Carlito-Bold.ttf");

    //renderText(characters, "std::string", vec2{20.f, 20.f}, 1.0, vec3{0.f, 200.f, 0.f});
    //renderText(characters, "This is sample text", vec2{25.0f, 25.0f}, 1.0f, vec3{0.5, 0.8f, 0.2f});
}

bool Game::registerButton(Sprite &btn, vec2 location, Button::OnClickFunc callback)
{
    buttons.emplace_back(btn, location, callback);
    return true;
}

/*
bool Game::removeButton(Sprite* btn) {
    buttonCallbacks.erase(btn);
=======
bool Game::registerButton(Sprite btn, vec2 location, ButtonOnClickFunc callback) {
    buttonCallbacks[&btn] = callback;
    buttonPositions[&btn] = location;
    return true;
}

bool Game::removeButton(Sprite btn) {
    buttonCallbacks.erase(&btn);
>>>>>>> Stashed changes
    return true;
}
*/
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
        world->onClick2(button, action, viewX, viewY);
        //world->on_key(button,action, viewX, viewY);
        // world->on_key2(button,action,viewX,viewY);
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

void Game::onKey2(int key, int scancode, int action)
{
    vec2 movDir = {0, 0};

    if (action == GLFW_PRESS)
    {

        switch (key)
        {
        case GLFW_KEY_W:
            movDir.y -= 10;
            break;
        case GLFW_KEY_S:
            movDir.y += 10;
            break;
        case GLFW_KEY_A:
            movDir.x -= 10;
            break;
        case GLFW_KEY_D:
            movDir.x += 10;
            break;
        default:
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_W:
            movDir.y += 10;
            break;
        case GLFW_KEY_S:
            movDir.y -= 10;
            break;
        case GLFW_KEY_A:
            movDir.x += 10;
            break;
        case GLFW_KEY_D:
            movDir.x -= 10;
            break;
        default:
            break;
        }
    }
    pirate.movement(movDir);
}

//void Game::on_key2(int key, int scancode, int action) {
//    if (action == GLFW_PRESS) {
//
//        switch (key) {
//            case GLFW_KEY_W:
//                pirate.p_position.y -= 1;
//                break;
//            case GLFW_KEY_S:
//                pirate.p_position.y += 1;
//                break;
//            case GLFW_KEY_A:
//                pirate.p_position.x -= 1;
//                break;
//            case GLFW_KEY_D:
//                pirate.p_position.x += 1;
//                break;
//            default:
//                break;
//        }
//    } else if (action == GLFW_RELEASE) {
//        switch (key) {
//            case GLFW_KEY_W:
//                pirate.p_position.y += 1;
//                break;
//            case GLFW_KEY_S:
//                pirate.p_position.y -= 1;
//                break;
//            case GLFW_KEY_A:
//                pirate.p_position.x += 1;
//                break;
//            case GLFW_KEY_D:
//                pirate.p_position.x -= 1;
//                break;
//            default:
//                break;
//        }
//    if (action == GLFW_PRESS && key == GLFW_KEY_D) {
//
//        pirate.moveRight = true;
//
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_D) {
//
//        pirate.moveRight = false;
//
//    } else if (action == GLFW_PRESS && key == GLFW_KEY_A) {
//
//        pirate.moveLeft = true;
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_A) {
//
//        pirate.moveLeft = false;
//
//    } else if (action == GLFW_PRESS && key == GLFW_KEY_W) {
//
//        pirate.moveUp = true;
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_W) {
//
//        pirate.moveUp = false;
//
//    } else if (action == GLFW_PRESS && key == GLFW_KEY_S) {
//
//        pirate.moveDown = true;
//
//    } else if (action == GLFW_RELEASE && key == GLFW_KEY_S) {
//
//        pirate.moveDown = false;
//
//    }
//    }
//}
/*
#include <ft2build.h>
#include FT_FREETYPE_H

struct vec2l
{
    uint64_t x, y;
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

std::map<GLchar, Character> loadFont(const char *filename)
{
    std::map<GLchar, Character> Characters;
    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, filename, 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
            texture,
            vec2l{face->glyph->bitmap.width, face->glyph->bitmap.rows},
            vec2l{face->glyph->bitmap_left, face->glyph->bitmap_top},
            face->glyph->advance.x};
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return Characters;
}

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

*/