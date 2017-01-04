#include "State_Playing.h"

namespace State
{
    State_Playing::State_Playing(sf::RenderWindow* window)
    : State_Base(window)
    {
        m_world = std::make_unique<World>();
        m_world->initWorld(*m_window);
    }

    void State_Playing::input()
    {

    }

    void State_Playing::update(const float dt)
    {
        m_world->updateWorld(dt);
    }

    void State_Playing::render()
    {
        m_world->renderWorld();
    }
}
