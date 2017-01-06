#ifndef CINEMATICCAMERA_H
#define CINEMATICCAMERA_H

#include "Camera.h"

class CinematicCamera : public Camera
{
private:
    glm::vec3 eye;
    glm::vec3 lookingAt;
    glm::vec3 up = glm::vec3(0, -1, 0);

    glm::mat4 modelview;
    glm::mat4 projection;
    glm::mat4 mvp;

public:
    CinematicCamera();

    virtual void update(const float dt) override;

    const glm::vec3& get_right();
    const glm::vec3& get_p_up(const glm::vec3& right);

    const glm::vec3& getEyeVector()    { return eye; }
    const glm::vec3& getObjectVector() { return lookingAt; }
    const glm::vec3& getUp()           { return up; }
};

#endif // CINEMATICCAMERA_H
