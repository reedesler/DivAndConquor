#ifndef DIVCONQ_LABEL_H
#define DIVCONQ_LABEL_H

#include "Sprite.hpp"
#include "Common.hpp"
#include "Ui/UiCallback.h"
#include <chrono>
#include <Ui/UiElement.h>
#include "TextRenderer.hpp"

class Label : public UiElement
{
  public:
    Label(std::string textStr, int fontSize, vec2 location, std::string fontPath = "Carlito-Bold.ttf", UiCallback::OnClickFunc callback = nullptr)
        : UiElement(*new Sprite, location, callback), text(textStr.c_str()), fontSize(fontSize)
    {
        tr.init((fonts_path() + fontPath).c_str());
    };
    void Draw(const mat3 &projection) override;
    const char *text;
    int fontSize;
    std::array<GLfloat, 4> color;

    using UiElement::UiElement;

  private:
    UiCallback::OnClickFunc callback;
    TextRenderer tr;
};

#endif //DIVCONQ_LABEL_H