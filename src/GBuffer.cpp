#include "GBuffer.h"

namespace bag
{
    std::vector<GLfloat> quadVertices = {
        // Positions
        -1.0f,  1.0f, 0.0f, // 0
        -1.0f, -1.0f, 0.0f, // 1
         1.0f, -1.0f, 0.0f, // 2
         1.0f,  1.0f, 0.0f  // 3
    };

    std::vector<GLfloat> quadTexCoods = {
        // Tex Coords
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    std::vector<GLuint> quadIndices = {
        // Indices
        0, 1, 2, 0, 2, 3
    };
}

bool GBuffer::init(unsigned int width, unsigned int height)
{
    // create FBO
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

    // Create gbuffer textures
    glGenTextures(GBUFFER_NUM_TEXTURES, m_textures);

    // Bind FBOs to each type
    for (unsigned int i = 0; i < GBUFFER_NUM_TEXTURES; i++)
    {
        glBindTexture(GL_TEXTURE_2D, m_textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
    }

    // Enable writing to textures
    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(GBUFFER_NUM_TEXTURES, drawBuffers);

    // Render buffer object
    glGenRenderbuffers(1, &m_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
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

void GBuffer::bindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void GBuffer::bindForReading()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

void GBuffer::setReadBuffer(GBUFFER_TEXTURE_TYPE TextureType)
{
    glReadBuffer(GL_COLOR_ATTACHMENT0 + TextureType);
}


GBuffer::GBuffer()
{
    //ctor
}

GBuffer::~GBuffer()
{
    //dtor
}
