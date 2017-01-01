#include "SkyDome.h"

SkyDome::SkyDome(StaticShader& sh)
: Entity(Loader::loadObjModel("dat/skydome.obj"), Loader::loadTexture("dat/skypolar.jpg"))
, shader(&sh)
{
    this->scale     = 1000.f;
    this->position  = glm::vec3(0, -50, 0);
}

void SkyDome::draw()
{
    shader->isEntity(true);
    shader->enableLighting(false);
    shader->loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_textureID);

    glBindVertexArray(mesh->getVaoID());
    glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    shader->enableLighting(true);
}

void SkyDome::update(const float dt)
{
    this->rotation  = sf::Vector3f(0, this->rotation.y + (dt * 0.02f), 0); //this->rotation.y + 0.015

    createTransformationMatrix();
}
