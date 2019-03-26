#include "Ui/VectorButton.hpp"
#include "Ui/Polygon.hpp"

void VectorButton::Draw(const mat3 &projection)
{

    float sx = 2.0 / 1200;
    float sy = 2.0 / 800;

    Polygon background;
    // Draw a rectangle from the 2 triangles using 6 indices

    GLfloat vertices[] = {
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // Top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f,  // Top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f // Bottom-left
    };
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0};
    background.init(vertices, elements, shader_path("button.vs"), shader_path("button.fs"));
    background.render();

    /* Set font size to 48 pixels, color to black */
    glm::vec4 translucent_black(0, 0, 0, 0.5);
    tr.config(fontSize, translucent_black);

    /* Effects of alignment */
    tr.draw(primaryText, pos.x + 8 * sx, pos.y + 50 * sy, sx, sy);
    if (inSeperateLines)
    {
        tr.draw(auxText, pos.x + 8 * sx, pos.y - 50 * sy, sx, sy);
    }
}
