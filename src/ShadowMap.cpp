#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
    // Generate FBO
    glGenFramebuffers(1, &depthMapFBO);

    // Generate the Texture
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    // Texture Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Attach texture to frame-buffer
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Set up light projection matrix
    m_depthShader.use();
    lightProjection = glm::ortho(-10.f, 10.f, -10.f, 10.0f, near_plane, far_plane);
    m_depthShader.stop();
}

void ShadowMap::setLightViewMatrix(const glm::vec3& lightPos, const glm::vec3& lightPointAt)
{
    this->lightView         = glm::lookAt(lightPos, lightPointAt, glm::vec3(0, 1, 0));
    this->lightSpaceMatrix  = lightProjection * lightView;

    this->m_depthShader.loadLightSpaceMatrix(lightSpaceMatrix);
}

void ShadowMap::loadModelMatrix(const glm::mat4& matrix)
{
    this->m_depthShader.loadModelMatrix(matrix);
}

void ShadowMap::configureDepthPass()
{
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    m_depthShader.use();
    glClear(GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::bindDepthFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
}

void ShadowMap::bindDepthTexture()
{
    glBindTexture(GL_TEXTURE_2D, depthMap);
}

const glm::mat4& ShadowMap::getLightSpaceMatrix()
{
    return this->lightSpaceMatrix;
}

DepthShader* ShadowMap::getDepthShader()
{
    return &m_depthShader;
}
