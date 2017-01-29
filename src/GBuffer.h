#ifndef GBUFFER_H
#define GBUFFER_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

#include "GLError.h"

class GBuffer
{
public:
    enum GBUFFER_TEXTURE_TYPE {
        GBUFFER_TEXTURE_TYPE_POSITION = 0,
        GBUFFER_TEXTURE_TYPE_NORMAL,
        GBUFFER_TEXTURE_TYPE_ALBEDO,
        GBUFFER_NUM_TEXTURES
    };

private:
    GLuint m_fbo;
    GLuint m_textures[GBUFFER_NUM_TEXTURES];
    GLuint m_rbo;

public:
    GBuffer();
    ~GBuffer();

    bool init(unsigned int width, unsigned int height);

    void bindForWriting();
    void bindForReading();
    void setReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);

    void unbindFramebuffer();
    void bindTexture(GBUFFER_TEXTURE_TYPE TextureType);
};

namespace bag
{
    extern std::vector<GLfloat> quadVertices;
    extern std::vector<GLfloat> quadTexCoods;
    extern std::vector<GLuint> quadIndices;
}

#endif // GBUFFER_H
