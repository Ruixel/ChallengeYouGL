#include "Cube.h"

std::vector<GLfloat> vertices = {
     0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left
};

std::vector<GLuint> indices = {
    0, 1, 3,
    1, 2, 3
};

std::vector<GLfloat> texCoords = {
    1.f, 1.f,
    1.f, 0.f,
    0.f, 0.f,
    0.f, 1.f
};

Cube::Cube(Loader& loader)
: Entity(loader)
{
    //this->mGame = mainGame;
    this->mesh = mLoader->loadToVAO(vertices, indices, texCoords);
}

void Cube::draw()
{
    glBindVertexArray(mesh->getVaoID());
    glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Cube::update(const float dt)
{
    //
}
