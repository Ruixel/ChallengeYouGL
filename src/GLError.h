#ifndef GLERROR_H_INCLUDED
#define GLERROR_H_INCLUDED

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <string>

namespace bag
{
    void checkForGLerrors();
}

#endif // GLERROR_H_INCLUDED
