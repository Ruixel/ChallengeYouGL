#ifndef POSTFX_H
#define POSTFX_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
#include <memory>

#include "RawModel.h"
#include "BasicShader.h"
#include "GLError.h"

class PostFX
{
private:
    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_textureid;

    // Shader
    BasicShader m_screenShader;
    GLuint location_theme;

public:
    PostFX();
    ~PostFX();

    bool init(unsigned int width, unsigned int height);

    void bindFramebuffer();
    void unbindFramebuffer();

    void bindTexture();

    void changeTheme(int theme);

    void renderScene(const std::unique_ptr<RawModel>& quadVao);
};

#endif // POSTFX_H
