#include "WorldSpawn.h"

std::vector<GLfloat> v = {
     0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left
};

std::vector<GLuint> i = {
    0, 1, 3,
    1, 2, 3
};

std::vector<GLfloat> n = {
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    0, 0, 1
};

WorldSpawn::WorldSpawn(StaticShader* sh)
:   shader(sh)
{
    cyQuad  q1;
    q1.v1 = glm::vec2(0     / WORLD_SIZE, 400   / WORLD_SIZE);
    q1.v2 = glm::vec2(400   / WORLD_SIZE, 400   / WORLD_SIZE);
    q1.v3 = glm::vec2(400   / WORLD_SIZE, 0     / WORLD_SIZE);
    q1.v4 = glm::vec2(0     / WORLD_SIZE, 0     / WORLD_SIZE);

    cyTexture t1;
    t1.texture = 1;

    cyFloor f1;
    f1.coordinates   = q1;
    f1.topSurface    = t1;
    f1.bottomSurface = t1;

    floors.push_back(f1);
    this->generateWorldMesh();
}

void WorldSpawn::generateWorldMesh()
{
    std::vector<GLfloat> vertices;
    std::vector<GLuint>  indices;
    std::vector<GLfloat> t_Coords;

    // FLOORS
    uint16_t c = 0;
    for (auto f : floors)
    {
        // Vertices
       /* vertices.insert(vertices.end(), {f.coordinates.v2.x, 0, f.coordinates.v2.y});
        vertices.insert(vertices.end(), {f.coordinates.v3.x, 0, f.coordinates.v3.y});
        vertices.insert(vertices.end(), {f.coordinates.v4.x, 0, f.coordinates.v4.y});
        vertices.insert(vertices.end(), {f.coordinates.v1.x, 0, f.coordinates.v1.y});*/
        vertices.insert(vertices.end(), {1, 1, 0});
        vertices.insert(vertices.end(), {1, 0, 0});
        vertices.insert(vertices.end(), {0, 0, 0});
        vertices.insert(vertices.end(), {0, 1, 0});

        // Triangles
        indices.insert (indices.end(),  {c, c+1, c+3});
        indices.insert (indices.end(),  {c+1, c+2, c+3});

        // Texture Coordinates
        t_Coords.insert(t_Coords.end(), {0, 0, 0, 0, 0, 0, 0, 0});

        c += 4;
    }

    this->mesh = Loader::loadToVAO(v, i, t_Coords, n);
    this->m_textureID = Loader::loadTexture("iceman.jpg");
}

void WorldSpawn::draw()
{
    shader->use();
    shader->loadTransformationMatrix(transformationMatrix);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_textureID);

    glBindVertexArray(mesh->getVaoID());
    glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    shader->stop();
}

void WorldSpawn::update(const float dt)
{
    this->rotation  = sf::Vector3f(0, this->rotation.y + 0.015, this->rotation.z + 0.01);
    this->scale     = 2.5f;

    createTransformationMatrix();
}
