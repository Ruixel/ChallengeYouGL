#ifndef STATICSHADER_H
#define STATICSHADER_H

#include "ShaderProgram.h"
#include "Camera.h"
#include "CinematicCamera.h"

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
   int location_viewMatrix              = 0;

   int location_enableLighting          = 0;
   int location_isEntity            = 0;

public:
    StaticShader();
    ~StaticShader() = default;

    void loadTransformationMatrix(const glm::mat4& matrix);
    void loadProjectionMatrix(const glm::mat4& projectionMatrix);
    void loadViewMatrix(Camera& cam);
    void loadViewMatrix(CinematicCamera& cam, float aperture, const glm::vec3& bokeh, const glm::vec3& p_up);

    void enableLighting(bool enable);
    void isEntity(bool enable);
};

#endif // STATICSHADER_H
