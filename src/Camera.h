#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraTarget, cameraDirection;

public:
    Camera();

    glm::mat4 generateProjectionMatrix(float aspectRatio);
    glm::mat4 generateViewMatrix();
};

#endif // CAMERA_H
