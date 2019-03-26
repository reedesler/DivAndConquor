//
// Created by DMa on 2019-03-20.
//

#ifndef DIVCONQ_VECTORBTN_HPP
#define DIVCONQ_VECTORBTN_HPP

#include "Ui/Label.hpp"

class VectorButton : public Label
{
  public:
    std::string primaryText;
    std::string auxText;
    int fontSize;
    bool inSeperateLines = false;
    std::array<GLfloat, 4> color;

    VectorButton(std::string textStr, int fontSize, vec2 location, bool inSeperateLines = False, std::string fontPath = "Carlito-Bold.ttf", UiCallback::OnClickFunc callback = nullptr)
        : UiElement(*new Sprite, location, callback), text(textStr.c_str()), fontSize(fontSize)
    {
        if (nlines == 1)
        {
            int nchars = textStr.length() / 2;
            for (int i = nchars; i > 1; i -= 1)
            {
                if (textStr[i] == ' ')
                {
                    primaryText = textStr.substr(0, i);
                    auxText = textStr.substr(i);
                    break;
                }
            }
        }
        tr.init((fonts_path() + fontPath).c_str());
    }

    void Draw(const mat3 &projection);
};

#endif //DIVCONQ_VECTORBTN_HPP
