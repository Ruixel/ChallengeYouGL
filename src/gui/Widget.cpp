#include "Widget.h"

namespace GUI
{
    Widget::Widget() {}
    Widget::Widget(Widget* parent)
    : m_parent(parent)
    {
        this->parent_size = m_parent->getSizeInPixels();
    }
    Widget::Widget(int width, int height)
    {
        this->parent_size = {width, height};
    }

    void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_rectangle, states);
    }

    void Widget::setColor(const sf::Color& color)
    {
        m_rectangle.setFillColor(color);
    }

    void Widget::setOutline(const sf::Color& color, int thickness)
    {
        m_rectangle.setOutlineColor(color);
        m_rectangle.setOutlineThickness(thickness);
    }

    void Widget::resetPositionAndSize()
    {
        this->m_rectangle.setPosition(this->getPositionInPixels());
        this->m_rectangle.setSize(this->getSizeInPixels());
    }

    void Widget::setParentSize(int width, int height)
    {
        this->parent_size = sf::Vector2f(width, height);
        this->resetPositionAndSize();
    }

    const sf::Vector2f& Widget::getSizeInPixels()
    {
        int width  = (parent_size.x * this->m_rectangle_size.left)  + this->m_rectangle_size.top;
        int height = (parent_size.y * this->m_rectangle_size.width) + this->m_rectangle_size.height;

        return {width, height};
    }

    const sf::Vector2f& Widget::getPositionInPixels()
    {
        int width  = (parent_size.x * this->m_rectangle_position.left)  + this->m_rectangle_position.top;
        int height = (parent_size.y * this->m_rectangle_position.width) + this->m_rectangle_position.height;

        return {width, height};
    }
}
