#include "Camera.h"

Camera::Camera()
{}

glm::mat4 Camera::generateProjectionMatrix(float aspectRatio)
{
    return glm::perspective(70.f, aspectRatio, 1.f, 1000.f);
}

glm::mat4 Camera::generateViewMatrix()
{
    glm::mat4 viewMatrix;
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_rotation.x), {1, 0, 0});
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_rotation.y), {0, 1, 0});
    viewMatrix = glm::rotate(viewMatrix, glm::radians(m_rotation.z), {0, 0, 1});

    return glm::translate(viewMatrix, -m_position);
}

// Stolen from Matt (Hopson97)

void Camera::update ()
{
    auto mouseMove = m_lastMosuePos - sf::Mouse::getPosition();

    m_rotation.y -= (float)mouseMove.x / 6.0;
    m_rotation.x -= (float)mouseMove.y / 6.0;

    m_lastMosuePos = sf::Mouse::getPosition();

    if      (m_rotation.x > 80 ) m_rotation.x = 80;
    else if (m_rotation.x < -80) m_rotation.x = -80;

    if      (m_rotation.y < 0 ) m_rotation.y = 360;
    else if (m_rotation.y > 360) m_rotation.y = 0;
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
