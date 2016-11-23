#include "WorldSpawn.h"

WorldSpawn::WorldSpawn(const char* levelPath, StaticShader* sh)
//:   Entity(Loader::loadToVAO(v, i, t, v), Loader::loadTexture("iceman.jpg"))
:   shader(sh)
{
    // Load file
    std::string level;

    std::ifstream level_string_buffer;
    level_string_buffer.exceptions(std::ifstream::badbit);

    // Variables & Iterators
    int ptr = 0;
    int bracket = 0;
    std::string obj_type = "";

    // Open File
    try {
        level_string_buffer.open(levelPath);

        std::stringstream ss_level;
        ss_level << level_string_buffer.rdbuf();

        level = ss_level.str();
        level_string_buffer.close();

    } catch (std::ifstream::failure e) {
        std::cout << "Issue loading file" << std::endl;
    }

    size_t str_length = level.length();
    while (ptr < str_length)
    {
        // Move up and down brackets
        if (level[ptr] == '[')
            bracket++;

        if (level[ptr] == ']')
            bracket--;

        // New type of object
        if (level[ptr] == '#')
        {
            size_t str_end = level.find(':', ptr);
            if (str_end != std::string::npos)
            {
                std::string obj_name = level.substr(ptr+1, str_end-ptr-1);
                std::cout << obj_name << std::endl;

                ptr = str_end;

                if (bracket == 1 && obj_name != "Floor")
                {
                    ptr += 2;

                    size_t info_end  = level.find(',', ptr);
                    std::string info = "N/A";
                    if (str_end != std::string::npos)
                        info = level.substr(ptr, info_end-ptr);

                    if (info[0] == '"')
                        info = info.substr(1, info.length() - 2);

                    if (obj_name == "name")         level_objs.name = info;
                    else if (obj_name == "levels")  level_objs.levels = info;
                    else if (obj_name == "version") level_objs.version = info;
                    else if (obj_name == "creator") level_objs.author = info;

                    std::cout << "Info: " << info << std::endl;
                }
            }
        }

        ptr++;
    }

    /*cyQuad  q1;
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

    floors.push_back(f1);*/

    // Generate Level Meshes
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

    this->mesh = Loader::loadToVAO(vertices, indices, t_Coords, normals);
    this->m_textureID = Loader::loadTexture("dat/000d1e44.jpg");

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
    //this->rotation  = sf::Vector3f(0, this->rotation.y + 0.015, this->rotation.z + 0.01);
    this->scale     = 20.0f;

    createTransformationMatrix();
}
