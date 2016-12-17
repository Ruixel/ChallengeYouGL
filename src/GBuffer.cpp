#include "GBuffer.h"

bool GBuffer::init(unsigned int width, unsigned int height)
{
    // create FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

    // Create gbuffer textures
    glGenTextures(GBUFFER_TEXTURE_TYPE_TOTAL, m_textures);
    glGenTextures(1, &m_depthTexture);

    // Bind FBOs to each type
    for (unsigned int i = 0; i < GBUFFER_TEXTURE_TYPE_TOTAL; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
    }

    // Depth Buffer
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                           m_depthTexture, 0);

    // Enable writing to textures
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                            GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    glDrawBuffers(GBUFFER_TEXTURE_TYPE_TOTAL, drawBuffers);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR: Cannot create FBOs successfully" << std::endl;
        bag::checkForGLerrors();

        return false;
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    return true;
}

GBuffer::GBuffer()
{
    //ctor
}

GBuffer::~GBuffer()
{
    //dtor
}
