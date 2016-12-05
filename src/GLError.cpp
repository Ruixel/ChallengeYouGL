#include "GLError.h"

#include <stdexcept>

namespace bag
{
    void checkForGLerrors()
    {
        GLenum errCode = glGetError();

        if ((errCode) != GL_NO_ERROR)
        {
            std::string error;

            switch(errCode) {
                    case GL_INVALID_OPERATION:
                        error="INVALID_OPERATION";
                        break;

                    case GL_INVALID_ENUM:
                        error="INVALID_ENUM";
                        break;

                    case GL_INVALID_VALUE:
                        error="INVALID_VALUE";
                        break;

                    case GL_OUT_OF_MEMORY:
                        error="OUT_OF_MEMORY";
                        break;

                    case GL_INVALID_FRAMEBUFFER_OPERATION:
                        error="INVALID_FRAMEBUFFER_OPERATION";
                        break;
                    default:
                        error="MISCELLANEOUS";
                        break;
            }

            //throw std::runtime_error("OpenGL error of type: " + error);
        }
    }
}
