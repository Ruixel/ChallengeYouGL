#include "StaticShader.h"

StaticShader::StaticShader()
{
    this->load(VERTEX_FILE, FRAGMENT_FILE);

    bindAttributes();
    getAllUniformLocations();
}

void StaticShader::bindAttributes()
{
    this->bindAttribute(0, "position");
    this->bindAttribute(1, "texCoords");
}

void StaticShader::getAllUniformLocations()
{
    location_transformationMatrix   = this->getUniformLocation("modelTransformation");
    location_projectionMatrix       = this->getUniformLocation("projectionTransformation");
}

void StaticShader::loadTransformationMatrix(const glm::mat4& matrix)
{
    this->loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(const glm::mat4& projectionMatrix)
{
    this->loadMatrix(location_projectionMatrix, projectionMatrix);
}
