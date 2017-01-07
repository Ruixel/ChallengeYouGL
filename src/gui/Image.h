#ifndef IMAGE_H
#define IMAGE_H

#include "gui/Widget.h"

#include <string>
#include <iostream>

namespace GUI
{
    class Image : public GUI::Widget
    {
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::Texture gui_texture;

        Widget* m_parent;

    public:
        Image(const std::string& file);
        Image(Widget* parent, const std::string& file);
        Image(int width, int height, const std::string& file);
    };
}

#endif // IMAGE_H
