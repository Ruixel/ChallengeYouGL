#ifndef CUBE_H
#define CUBE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

#include "Entity.h"

class Cube : public Entity
{
private:

public:
    Cube(Loader& loader);

    void draw();
    void update(const float dt);
};

#endif // CUBE_H
