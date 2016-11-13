#ifndef CAMERA_H
#define CAMERA_H

#include <glm/common.hpp>

class Camera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget, cameraDirection;

public:
    Camera();
};

#endif // CAMERA_H
