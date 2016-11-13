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

Cube::Cube(StaticShader* sh)
//: Entity(Loader::loadToVAO(vertices, indices, texCoords, vertices))
: Entity(Loader::loadObjModel("cube.obj"))
, shader(sh)
{}

void Cube::draw()
{
    shader->use();
    shader->loadTransformationMatrix(transformationMatrix);

    glBindVertexArray(mesh->getVaoID());
    glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader->stop();
}

void Cube::update(const float dt)
{
    this->rotation  = sf::Vector3f(0, this->rotation.y + 0.015, this->rotation.z + 0.01);
    this->scale     = 1.f;

    createTransformationMatrix();
}
