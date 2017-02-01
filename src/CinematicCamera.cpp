#include "CinematicCamera.h"

CinematicCamera::CinematicCamera()
{
    this->m_position = Vector3(20, 35, -20);
    this->m_rotation = Vector3(-PI / 6, -PI / 4, 0);
}

void CinematicCamera::update(const float dt)
{

    //const float dt = deltaTime * 100;

    auto mouseMove = m_lastMousePos - sf::Mouse::getPosition();

    m_rotation.y -= (float)mouseMove.x / 260.0;
    m_rotation.x -= (float)mouseMove.y / 260.0;

    if      (m_rotation.x > HALF_PI ) m_rotation.x = HALF_PI;
    else if (m_rotation.x < -HALF_PI) m_rotation.x = -HALF_PI;

    if      (m_rotation.y < 0 ) m_rotation.y = 2*PI - 0;
    else if (m_rotation.y > 2*PI - 0) m_rotation.y = 0;

    auto yaw    = this->m_rotation.y + glm::radians(90.f);
    auto pitch  = this->m_rotation.x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->m_position = Vector3(m_position.x - (cos(yaw) * cos(pitch)) * .2 * dt, m_position.y - sin(pitch) * .2 * dt, m_position.z - (sin(yaw) * cos(pitch)) * .2 * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->m_position = Vector3(m_position.x + (cos(yaw) * cos(pitch)) * .2 * dt, m_position.y + sin(pitch) * .2 * dt, m_position.z + (sin(yaw) * cos(pitch)) * .2 * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->m_position = Vector3(m_position.x + cos(yaw + HALF_PI) * .2 * dt, m_position.y, m_position.z + sin(yaw + HALF_PI) * .2 * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->m_position = Vector3(m_position.x - cos(yaw + HALF_PI) * .2 * dt, m_position.y, m_position.z - sin(yaw + HALF_PI) * .2 * dt);
    }

    //sf::Vector2u windowSize = m_window->getSize();
    //sf::Mouse::setPosition(sf::Vector2i(windowSize.x / 2, windowSize.y / 2), *m_window);

    m_lastMousePos = sf::Mouse::getPosition();

}

