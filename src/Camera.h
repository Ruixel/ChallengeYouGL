#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>

#define PI (3.141592653589793)
#define HALF_PI (1.570796326794897)

typedef glm::vec3 Vector3;

class Camera
{
private:
    Vector3 m_position = Vector3(0, 2, 0);
    Vector3 m_rotation = Vector3(-HALF_PI, HALF_PI, 0);

    sf::Vector2i m_lastMousePos;
    sf::Window* m_window = nullptr;

    bool camera_locked = true;

public:
    Camera();
    void init(sf::Window* window);

    glm::mat4 generateProjectionMatrix(float aspectRatio);
    glm::mat4 generateViewMatrix();

    const Vector3& getPosition () const;
    const Vector3& getRotation () const;

    void setPosition (const Vector3& position);
    void setRotation (const Vector3& rotation);

    void movePosition (const Vector3& position);

    void toggleLockMouse();

    void move (float dt);
    void update ();
};

#endif // CAMERA_H
