#ifndef GBUFFER_H
#define GBUFFER_H

#include "GLError.h"

#define GLEW_STATIC
#include <GL/glew.h>

class GBuffer
{
public:
    enum class GBUFFER_TEXTURE_TYPE
    {
        POSITION,
        DIFFUSE,
        NORMAL,
        TEXCOORD,
        TOTAL,
    };


private:
    GLuint m_fbo;
    GLuint m_textures[static_cast<int>(GBUFFER_TEXTURE_TYPE::TOTAL)];
    GLuint m_depthTexture;

public:
    GBuffer();
    ~GBuffer();

    bool init(unsigned int width, unsigned int height);

    void bindForWriting();
    void bindForReading();
};

constexpr static int GBUFFER_TEXTURE_TYPE_TOTAL = static_cast<int>(GBuffer::GBUFFER_TEXTURE_TYPE::TOTAL);

#endif // GBUFFER_H
