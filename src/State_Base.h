#ifndef STATE_BASE_H
#define STATE_BASE_H

#include <SFML/Graphics.hpp>

namespace State
{
    class State_Base
    {
    protected:
        //MainGame* m_app;
        sf::RenderWindow* m_window;

    public:
        //State_Base(MainGame* app);
        State_Base(sf::RenderWindow* window);

        virtual void input()                = 0;
        virtual void update(const float dt) = 0;
        virtual void render()               = 0;
    };
}

#endif // STATE_BASE_H
