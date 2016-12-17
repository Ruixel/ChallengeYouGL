#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "ShaderProgram.h"
#include "Camera.h"

#include <glm/glm.hpp>

class BasicShader : public ShaderProgram
{
private:
   void bindAttributes();
   void getAllUniformLocations();

public:
    BasicShader(const GLchar* VERTEX_FILE, const GLchar* FRAGMENT_FILE);
    ~BasicShader() = default;

    void loadProjectionMatrix(const glm::mat4& projectionMatrix);
};

#endif // BASICSHADER_H
