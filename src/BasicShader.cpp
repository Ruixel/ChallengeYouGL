#include "BasicShader.h"

BasicShader::BasicShader(const GLchar* VERTEX_FILE, const GLchar* FRAGMENT_FILE)
{
    this->load(VERTEX_FILE, FRAGMENT_FILE);

    bindAttributes();
    getAllUniformLocations();
}

void BasicShader::bindAttributes()
{
    this->bindAttribute(0, "position");
    this->bindAttribute(1, "texCoords");
}

void BasicShader::getAllUniformLocations()
{}

void BasicShader::loadProjectionMatrix(const glm::mat4& projectionMatrix)
{}
