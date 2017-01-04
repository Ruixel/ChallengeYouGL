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
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::T)
                    m_world->getCamera()->toggleLockMouse();
                break;

            case sf::Event::Closed :
                m_window->close();
                break;

            case sf::Event::Resized :
                {
                    sf::FloatRect area(0, 0, event.size.width, event.size.height);
                    std::cout << "Width: " << area.width << std::endl;

                    glViewport(0, 0, area.width, area.height);
                    m_window->setSize({area.width, area.height});
                    m_window->setView(sf::View(area));

                    m_world->setupCameraUniforms();

                    break;
                }

            default:
                break;
            }
        }
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
