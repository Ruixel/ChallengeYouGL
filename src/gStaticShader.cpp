#include "gStaticShader.h"

gStaticShader::gStaticShader()
{
    this->load(VERTEX_FILE, FRAGMENT_FILE);

    bindAttributes();
    getAllUniformLocations();
}

void gStaticShader::bindAttributes()
{
    this->bindAttribute(0, "position");
    this->bindAttribute(1, "texCoords");
    this->bindAttribute(2, "normal");


}

void gStaticShader::getAllUniformLocations()
{
    location_transformationMatrix   = this->getUniformLocation("modelTransformation");
    location_projectionMatrix       = this->getUniformLocation("projectionTransformation");
    location_viewMatrix             = this->getUniformLocation("viewTransformation");

    location_enableLighting         = this->getUniformLocation("enableLighting");
    location_isEntity               = this->getUniformLocation("isEntity");
}

void gStaticShader::loadTransformationMatrix(const glm::mat4& matrix)
{
    this->loadMatrix(location_transformationMatrix, matrix);
}

void gStaticShader::loadProjectionMatrix(const glm::mat4& projectionMatrix)
{
    this->loadMatrix(location_projectionMatrix, projectionMatrix);
}

void gStaticShader::loadViewMatrix(Camera& cam)
{
    this->loadMatrix(location_viewMatrix, cam.generateViewMatrix());
}

void gStaticShader::loadViewMatrix(CinematicCamera& cam, float aperture, const glm::vec3& bokeh, const glm::vec3& p_up)
{
    glm::mat4 view_matrix = glm::lookAt(cam.getEyeVector() + aperture * bokeh, cam.getObjectVector(), p_up);
    this->loadMatrix(location_viewMatrix, view_matrix);
}

void gStaticShader::enableLighting(bool enable)
{
    this->loadBoolean(location_enableLighting, enable);
}

void gStaticShader::isEntity(bool isEntity)
{
    this->loadBoolean(location_isEntity, isEntity);
}
