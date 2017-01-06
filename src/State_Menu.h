#ifndef STATE_MENU_H
#define STATE_MENU_H

#include <memory>
#include <iostream>

#include "State_Base.h"
#include "MenuBackground.h"
#include "gui/Widget.h"

namespace State
{
    class State_Menu : public State_Base
    {
    private:
        std::unique_ptr<MenuBackground> m_background;
        sf::RenderWindow* window;

    public:
        State_Menu(sf::RenderWindow* window);
        ~State_Menu();

        void input()                override;
        void update(const float dt) override;
        void render()               override;
    };
}

#endif // STATE_MENU_H
