#ifndef POSTFX_H
#define POSTFX_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

#include "GLError.h"

class PostFX
{
private:
    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_textureid;

public:
    ~PostFX();

    bool init(unsigned int width, unsigned int height);

    void bindFramebuffer();
    void unbindFramebuffer();

    void bindTexture();
};

#endif // POSTFX_H
