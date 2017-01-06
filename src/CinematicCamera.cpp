#include "CinematicCamera.h"

CinematicCamera::CinematicCamera()
{
    eye = glm::vec3(5, 40, -30);
    lookingAt = glm::vec3(-15, 70, -70);
}

void CinematicCamera::update(const float dt)
{

}

const glm::vec3& CinematicCamera::get_right()
{
    return glm::normalize(glm::cross(lookingAt - eye, up));
}

const glm::vec3& CinematicCamera::get_p_up(const glm::vec3& right)
{
    return glm::normalize(glm::cross(lookingAt - eye, right));
}
