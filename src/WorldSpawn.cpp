#include "WorldSpawn.h"

WorldSpawn::WorldSpawn(StaticShader* sh)
//:   Entity(Loader::loadToVAO(v, i, t, v), Loader::loadTexture("iceman.jpg"))
:   shader(sh)
{
    cyQuad  q1;
    q1.v1 = glm::vec3((0   - 200)    / WORLD_SIZE, 0, (400 - 200)   / WORLD_SIZE);
    q1.v2 = glm::vec3((300 - 200)    / WORLD_SIZE, 0, (400 - 200)   / WORLD_SIZE);
    q1.v3 = glm::vec3((400 - 200)    / WORLD_SIZE, 0, (50   - 200)   / WORLD_SIZE);
    q1.v4 = glm::vec3((0   - 200)    / WORLD_SIZE, 0, (0   - 200)   / WORLD_SIZE);

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
    std::vector<GLfloat> vertices, t_Coords, normals;
    std::vector<GLuint>  indices;

    // FLOORS
    uint16_t c = 0;
    for (auto f : floors)
    {
        // Vertices
        vertices.insert(vertices.end(), {f.coordinates.v2.x, 0, f.coordinates.v2.z});
        vertices.insert(vertices.end(), {f.coordinates.v3.x, 0, f.coordinates.v3.z});
        vertices.insert(vertices.end(), {f.coordinates.v4.x, 0, f.coordinates.v4.z});
        vertices.insert(vertices.end(), {f.coordinates.v1.x, 0, f.coordinates.v1.z});

        // Triangles
        indices.insert (indices.end(),  {c, c+1, c+3});
        indices.insert (indices.end(),  {c+1, c+2, c+3});

        // Texture Coordinates
        t_Coords.insert(t_Coords.end(), {f.coordinates.v2.x*3.0, f.coordinates.v2.z*3.0});
        t_Coords.insert(t_Coords.end(), {f.coordinates.v3.x*3.0, f.coordinates.v3.z*3.0});
        t_Coords.insert(t_Coords.end(), {f.coordinates.v4.x*3.0, f.coordinates.v4.z*3.0});
        t_Coords.insert(t_Coords.end(), {f.coordinates.v1.x*3.0, f.coordinates.v1.z*3.0});

        // Normals
        glm::vec3 normal = glm::cross(f.coordinates.v2 - f.coordinates.v1, f.coordinates.v3 - f.coordinates.v1);
        normals.insert(normals.end(), {normal.x, normal.y, normal.z});
        normals.insert(normals.end(), {normal.x, normal.y, normal.z});
        normals.insert(normals.end(), {normal.x, normal.y, normal.z});
        normals.insert(normals.end(), {normal.x, normal.y, normal.z});

        c += 4;
    }

    this->mesh = Loader::loadToVAO(vertices, indices, t_Coords, vertices);
    this->m_textureID = Loader::loadTexture("000d1e44.jpg");

    std::cout << "Vertex count: " << mesh->getVaoID() << std::endl;
}

void WorldSpawn::draw()
{
    shader->loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_textureID);

    glBindVertexArray(mesh->getVaoID());
    glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}

void WorldSpawn::update(const float dt)
{
    this->position  = glm::vec3(0, -.6f, 0);
    this->scale     = 20.0f;

    createTransformationMatrix();
}
