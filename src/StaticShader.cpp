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
    this->bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations()
{
    location_transformationMatrix   = this->getUniformLocation("modelTransformation");
    location_projectionMatrix       = this->getUniformLocation("projectionTransformation");
    location_viewMatrix             = this->getUniformLocation("viewTransformation");

    location_enableLighting         = this->getUniformLocation("enableLighting");
    location_isEntity               = this->getUniformLocation("isEntity");
}

void StaticShader::loadTransformationMatrix(const glm::mat4& matrix)
{
    this->loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(const glm::mat4& projectionMatrix)
{
    this->loadMatrix(location_projectionMatrix, projectionMatrix);
}

void StaticShader::loadViewMatrix(Camera& cam)
{
    this->loadMatrix(location_viewMatrix, cam.generateViewMatrix());
}

void StaticShader::loadViewMatrix(CinematicCamera& cam, float aperture, const glm::vec3& bokeh, const glm::vec3& p_up)
{
    glm::mat4 view_matrix = glm::lookAt(cam.getEyeVector() + aperture * bokeh, cam.getObjectVector(), p_up);
    this->loadMatrix(location_viewMatrix, view_matrix);
}

void StaticShader::enableLighting(bool enable)
{
    this->loadBoolean(location_enableLighting, enable);
}

void StaticShader::isEntity(bool isEntity)
{
    this->loadBoolean(location_isEntity, isEntity);
}
