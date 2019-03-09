#ifndef DIVCONQ_BUTTON_H
#define DIVCONQ_BUTTON_H

#include "Sprite.hpp"
#include "Common.hpp"
#include "Ui/UiCallback.h"
#include <chrono>
#include <Ui/UiElement.h>


class Button : public UiElement
{
public:
    void Draw(const mat3 &projection) override;
    using UiElement::UiElement;

};

#endif //DIVCONQ_BUTTON_H