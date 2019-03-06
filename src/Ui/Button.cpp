#include "Ui/UiCallback.h"
#include "Ui/UiElement.h"

#include "Button.hpp"


void Button::Draw(const mat3 &projection)
{
    UpdateFlash();
    UiElement::Draw(projection);
}

