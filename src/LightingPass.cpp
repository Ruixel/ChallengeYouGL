#include "LightingPass.h"

LightingPass::LightingPass()
{
    this->load(VERTEX_FILE, FRAGMENT_FILE);

    bindAttributes();
    getAllUniformLocations();
}

void LightingPass::bindAttributes()
{
    this->use();
    this->loadInt(getUniformLocation("gPosition"),   0);
    this->loadInt(getUniformLocation("gNormal"),     1);
    this->loadInt(getUniformLocation("gAlbedoSpec"), 2);
    this->stop();
}

void LightingPass::getAllUniformLocations()
{
    location_viewPos = this->getUniformLocation("viewPos");
}

void LightingPass::setVec3LightSetting(uint8_t light_num, const std::string& property, const glm::vec3& vec)
{
    this->loadVector(getUniformLocation(("lights[" + std::to_string(light_num) + "]." + property).c_str()), vec);
}

void LightingPass::setFloatLightSetting(uint8_t light_num, const std::string& property, float value)
{
    this->loadFloat(getUniformLocation(("lights[" + std::to_string(light_num) + "]." + property).c_str()), value);
}

void LightingPass::setViewPosition(const Camera& camera)
{
    this->loadVector(location_viewPos, camera.getPosition());
}

void LightingPass::loadProjectionMatrix(const glm::mat4& matrix) {} // Not needed
