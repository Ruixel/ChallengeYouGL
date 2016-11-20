#ifndef GLERROR_H_INCLUDED
#define GLERROR_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <string>

namespace bag
{
    static void checkForGLerrors()
    {
        GLenum errCode;

        if ((errCode = glGetError()) != GL_NO_ERROR)
        {
            std::string error;

            switch(errCode) {
                    case GL_INVALID_OPERATION:              error="INVALID_OPERATION";      break;
                    case GL_INVALID_ENUM:                   error="INVALID_ENUM";           break;
                    case GL_INVALID_VALUE:                  error="INVALID_VALUE";          break;
                    case GL_OUT_OF_MEMORY:                  error="OUT_OF_MEMORY";          break;
                    case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
                    default:                                error="MISCELLANEOUS";          break;
            }

            //std::cerr << "Error: " << error.c_str() << std::endl;

        }
    }
}

#endif // GLERROR_H_INCLUDED
