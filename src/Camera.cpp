#include "Camera.h"

Camera::Camera()
{}

glm::mat4 Camera::generateProjectionMatrix(float aspectRatio)
{
    return glm::perspective(70.f, aspectRatio, 1.f, 1000.f);
}

glm::mat4 Camera::generateViewMatrix()
{

}
