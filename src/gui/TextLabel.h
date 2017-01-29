#ifndef TEXTLABEL_H
#define TEXTLABEL_H

#include "gui/Widget.h"

#include <vector>

namespace GUI
{
    enum class TextAlignment
    {
        LEFT, CENTER, RIGHT
    };

    class TextLabel : public GUI::Widget
    {
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::Font* text_font;
        sf::Text  m_text;

        TextAlignment text_alignment;

    public:
        TextLabel();

        //virtual void update();
    };
}

#endif // TEXTLABEL_H
