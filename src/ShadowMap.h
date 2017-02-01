#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#define GLEW_STATIC
#include <GL/glew.h>

#include "DepthShader.h"

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

const GLuint SHADOW_WIDTH  = 2048, SHADOW_HEIGHT = 2048;
const GLfloat near_plane = 1.0f, far_plane = 50.0f;
const GLfloat ortho_size = 20.0f;

class ShadowMap
{
private:
    DepthShader m_depthShader;

    GLuint depthMap;        // Texture
    GLuint depthMapFBO;     // Frame-buffer

    glm::mat4 lightProjection;
    glm::mat4 lightView;
    glm::mat4 lightSpaceMatrix;

    //sf::Window* m_window;   // Needed to revert glViewport back to normal

public:
    ShadowMap();

    void setLightViewMatrix(const glm::vec3& lightPos, const glm::vec3& lightPointAt);
    void loadModelMatrix(const glm::mat4& matrix);

    void configureDepthPass();

    void bindDepthFBO();
    void bindDepthTexture();

    const glm::mat4& getLightSpaceMatrix();
    DepthShader*     getDepthShader();
};

#endif // SHADOWMAP_H
