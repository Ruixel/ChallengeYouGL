#include "DepthShader.h"

DepthShader::DepthShader()
{
    this->load(VERTEX_FILE, FRAGMENT_FILE);

    bindAttributes();
    getAllUniformLocations();
}

void DepthShader::bindAttributes()
{
    this->bindAttribute(0, "position");
}

void DepthShader::getAllUniformLocations()
{
    location_lightSpaceMatrix = this->getUniformLocation("lightSpaceMatrix");
    location_modelMatrix      = this->getUniformLocation("model");
}

void DepthShader::loadLightSpaceMatrix(const glm::mat4& matrix)
{
    this->loadMatrix(location_lightSpaceMatrix, matrix);
}

void DepthShader::loadModelMatrix(const glm::mat4& matrix)
{
    this->loadMatrix(location_modelMatrix, matrix);
}

void DepthShader::loadProjectionMatrix(const glm::mat4& projectionMatrix)
{}
