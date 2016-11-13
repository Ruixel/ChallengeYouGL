#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "ShaderProgram.h"

#include <glm/glm.hpp>

class StaticShader : public ShaderProgram
{
private:
   const GLchar* VERTEX_FILE   = "shaders/StaticShader.vert";
   const GLchar* FRAGMENT_FILE = "shaders/StaticShader.frag";

   void bindAttributes();
   void getAllUniformLocations();

   int location_transformationMatrix    = 0;
   int location_projectionMatrix        = 0;

public:
    StaticShader();

    void loadTransformationMatrix(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& projectionMatrix);
};

#endif // STATICSHADER_H
