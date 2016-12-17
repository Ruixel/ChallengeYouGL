#include "WorldSpawn.h"

WorldSpawn::WorldSpawn(const char* levelPath, StaticShader& sh, Camera* camera)
//:   Entity(Loader::loadToVAO(v, i, t, v), Loader::loadTexture("iceman.jpg"))
:   shader(&sh)
,   m_camera(camera)
{
    CYLevelLoader::level_textures = &this->level_textures;
    //level_objs = CYLevelLoader::loadFromFile(levelPath);
    level_objs = CYLevelLoader::loadFromWebsite(51450);
}

void WorldSpawn::draw()
{
    shader->loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);

    texture_id previous_texture = CY_UNASSIGNED;
    for (auto& chunk : level_objs.chunks)
    {
        level_textures.bindTexture(chunk.textureID);

        glBindVertexArray(chunk.meshID->getVaoID());
        glDrawElements(GL_TRIANGLES, chunk.meshID->getVertexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}

void WorldSpawn::update(const float dt)
{
    this->position  = glm::vec3(0, -.6f, 0);
    this->scale     = 100.0f;

    createTransformationMatrix();
}
