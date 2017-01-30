#ifndef LIGHTINGPASS_H
#define LIGHTINGPASS_H

#include "ShaderProgram.h"
#include "Camera.h"

#include <string>
#include <glm/glm.hpp>

class LightingPass : public ShaderProgram
{
private:
    const GLchar* VERTEX_FILE   = "shaders/basicLightingPass.vert";
    const GLchar* FRAGMENT_FILE = "shaders/basicLightingPass.frag";

    void bindAttributes();
    void getAllUniformLocations();

    int location_viewPos = 0;

public:
    LightingPass();
    ~LightingPass() = default;

    void loadProjectionMatrix(const glm::mat4& matrix);

    void setVec3LightSetting (uint8_t light_num, const std::string& property, const glm::vec3& vec);
    void setFloatLightSetting(uint8_t light_num, const std::string& property, float value);

    void setViewPosition(const Camera& camera);
};

#endif // LIGHTINGPASS_H
