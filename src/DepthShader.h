#ifndef DEPTHSHADER_H
#define DEPTHSHADER_H

#include "ShaderProgram.h"

#include <glm/glm.hpp>

class DepthShader : public ShaderProgram
{
private:
   const GLchar* VERTEX_FILE   = "shaders/depthShader.vert";
   const GLchar* FRAGMENT_FILE = "shaders/depthShader.frag";

   void bindAttributes();
   void getAllUniformLocations();

   int location_lightSpaceMatrix = 0;
   int location_modelMatrix      = 0;

public:
    DepthShader();
    ~DepthShader() = default;

    void loadLightSpaceMatrix(const glm::mat4& matrix);
    void loadModelMatrix(const glm::mat4& matrix);

    void loadProjectionMatrix(const glm::mat4& projectionMatrix);
};

#endif // DEPTHSHADER_H
