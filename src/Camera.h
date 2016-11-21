#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>

typedef glm::vec3 Vector3;

class Camera
{
private:
    Vector3 m_position;
    Vector3 m_rotation;

    sf::Vector2i m_lastMousePos;

public:
    Camera();

    glm::mat4 generateProjectionMatrix(float aspectRatio);
    glm::mat4 generateViewMatrix();

    const Vector3& getPosition () const;
    const Vector3& getRotation () const;

    void setPosition (const Vector3& position);
    void setRotation (const Vector3& rotation);

    void movePosition (const Vector3& position);

    void move (float dt);
    void update (sf::Window* m_window);
};

#endif // CAMERA_H
