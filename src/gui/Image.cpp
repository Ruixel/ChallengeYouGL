#include "Image.h"

namespace GUI
{
    Image::Image(const std::string& file)
    {
        if (gui_texture.loadFromFile(file))
        {
            m_rectangle.setTexture(&gui_texture);
            m_rectangle.setFillColor(sf::Color(255, 255, 255, 255));

        } else {
            m_rectangle.setFillColor(sf::Color(255, 0, 0, 255));
            std::cout << "Issue loading file at: " << file << std::endl;
        }

    }
    Image::Image(Widget* parent, const std::string& file)
    : Image(file)
    {
        this->m_parent = parent;
        this->parent_size = m_parent->getSizeInPixels();
    }
    Image::Image(int width, int height, const std::string& file)
    : Image(file)
    {
        this->parent_size = {width, height};
    }

    void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_rectangle, states);
    }
}
