#ifndef CUBE_H
#define CUBE_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
#include <SFML/Graphics.hpp>

#include "OBJLoader.h"
#include "Entity.h"
#include "StaticShader.h"

class Cube : public Entity
{
private:
    StaticShader* shader;

public:
    Cube(StaticShader& sh);

    void draw();
    void update(const float dt);
};

#endif // CUBE_H
