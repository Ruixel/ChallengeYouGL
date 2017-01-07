#include "CinematicCamera.h"

CinematicCamera::CinematicCamera()
{
    this->m_position = Vector3(20, 35, -20);
    this->m_rotation = Vector3(-PI / 6, -PI / 4, 0);
}

void CinematicCamera::update(const float dt)
{

}

