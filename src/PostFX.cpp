#include "PostFX.h"


bool PostFX::init(unsigned int width, unsigned int height)
{
    // create FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

    glGenTextures(1, &m_textureid);
    glBindTexture(GL_TEXTURE_2D, m_textureid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureid, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Render buffer object
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR: Cannot create FBOs successfully" << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        bag::checkForGLerrors();

        return false;
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    return true;
}

void PostFX::bindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void PostFX::unbindFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostFX::bindTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_textureid);
}

PostFX::~PostFX()
{
    glDeleteFramebuffers(1, &m_fbo);
}
