#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

#include <SFML/Graphics.hpp>

namespace GUI
{
    class Widget : public sf::Drawable
    {
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    protected:
        sf::RectangleShape m_rectangle;

        sf::FloatRect m_rectangle_size;
        sf::FloatRect m_rectangle_position;
        sf::Vector2f parent_size;

        Widget* m_parent;
        std::vector<Widget*> children;

    public:
        Widget();
        Widget(Widget* parent);
        Widget(int width, int height);

        void setColor(const sf::Color& color);
        void setOutline(const sf::Color& color, int thickness);

        void resetPositionAndSize();
        void setSize  (const sf::FloatRect& rect) { m_rectangle_size = rect;     this->resetPositionAndSize(); }
        void setPos   (const sf::FloatRect& rect) { m_rectangle_position = rect; this->resetPositionAndSize(); }

        const sf::Vector2f& getPositionInPixels();
        const sf::Vector2f& getSizeInPixels();

        /*void setSizeScale  (const sf::FloatRect& rect) { m_rectangle_size_scale  = rect; }
        void setSizeOffset (const sf::FloatRect& rect) { m_rectangle_size_offset = rect; }
        void setPosScale   (const sf::FloatRect& rect) { m_rectangle_position_scale  = rect; }
        void setPosOffset  (const sf::FloatRect& rect) { m_rectangle_position_offset = rect; }*/
    };
}

#endif // WIDGET_H
