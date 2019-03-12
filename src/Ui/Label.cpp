#include "Ui/UiCallback.h"
#include "Ui/UiElement.h"

#include "Label.hpp"
#include <string>

void Label::Draw(const mat3 &projection)
{

    float sx = 2.0 / 1200;
    float sy = 2.0 / 800;


    /* Set font size to 48 pixels, color to black */
    glm::vec4 translucent_black(0, 0, 0, 0.5);
    tr.config(fontSize, translucent_black);

    /* Effects of alignment */
    tr.draw(text, pos.x + 8 * sx, pos.y - 50 * sy, sx, sy);
}

