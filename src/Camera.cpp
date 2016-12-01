#include "Camera.h"
#include <iostream>

Camera::Camera()
{}

void Camera::init(sf::RenderWindow& window)
{
    this->m_window = &window;
    m_window->setMouseCursorVisible(false);
}

glm::mat4 Camera::generateProjectionMatrix(float aspectRatio)
{
    return glm::perspective(70.f, aspectRatio, .1f, 1000.f);
}

glm::mat4 Camera::generateViewMatrix()
{
    glm::mat4 viewMatrix;
    viewMatrix = glm::rotate(viewMatrix, m_rotation.x, {1, 0, 0});
    viewMatrix = glm::rotate(viewMatrix, m_rotation.y, {0, 1, 0});
    viewMatrix = glm::rotate(viewMatrix, m_rotation.z, {0, 0, 1});

    return glm::translate(viewMatrix, -m_position);
}

// Remastered from Matt (Hopson97)

void Camera::update ()
{
    if (!camera_locked)
        return;

    auto mouseMove = m_lastMousePos - sf::Mouse::getPosition();

    m_rotation.y -= (float)mouseMove.x / 260.0;
    m_rotation.x -= (float)mouseMove.y / 260.0;

    if      (m_rotation.x > HALF_PI ) m_rotation.x = HALF_PI;
    else if (m_rotation.x < -HALF_PI) m_rotation.x = -HALF_PI;

    if      (m_rotation.y < 0 ) m_rotation.y = 2*PI;
    else if (m_rotation.y > 2*PI) m_rotation.y = 0;

    auto yaw    = this->m_rotation.y + glm::radians(90.f);
    auto pitch  = this->m_rotation.x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->m_position = Vector3(m_position.x - cos(yaw) * .2, m_position.y - sin(pitch) * .2, m_position.z - sin(yaw) * .2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->m_position = Vector3(m_position.x + cos(yaw) * .2, m_position.y + sin(pitch) * .2, m_position.z + sin(yaw) * .2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->m_position = Vector3(m_position.x + cos(yaw + HALF_PI) * .2, m_position.y, m_position.z + sin(yaw + HALF_PI) * .2);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->m_position = Vector3(m_position.x - cos(yaw + HALF_PI) * .2, m_position.y, m_position.z - sin(yaw + HALF_PI) * .2);
    }

    sf::Vector2u windowSize = m_window->getSize();
    sf::Mouse::setPosition(sf::Vector2i(windowSize.x / 2, windowSize.y / 2), *m_window);

    m_lastMousePos = sf::Mouse::getPosition();
}

void Camera::toggleLockMouse()
{
    camera_locked = !camera_locked;
    m_window->setMouseCursorVisible(!camera_locked);
}

bool Camera::getToggle()
{
    return camera_locked;
}

void Camera::setPosition(const Vector3& position)
{
    m_position = position;
}

void Camera::setRotation(const Vector3& rotation)
{
    m_rotation = rotation;
}


const Vector3& Camera::getPosition() const
{
    return this->m_position;
}

const Vector3& Camera::getRotation() const
{
    return this->m_rotation;
}

void Camera::movePosition(const Vector3& position)
{
    this->m_position += position;
}
