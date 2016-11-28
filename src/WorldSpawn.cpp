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

                } else {
                    int end_bracket = bracket;
                    int item_number = 1;
                    bool waitForNewItem = false;

                    ptr += 3;
                    bracket++;

                    // PLACEHOLDER VARIABLES
                    int item_bracket = 3;
                    std::vector<std::string>* properties = new std::vector<std::string>();

                    while (bracket > end_bracket && obj_name == "Floor")
                    {
                        // Move up and down brackets
                        if (level[ptr] == '[')
                            bracket++;

                        if (level[ptr] == ']')
                            bracket--;

                        // New Item
                        if (bracket < item_bracket)
                        {
                            if (!waitForNewItem)
                            {
                                // If floor, add level number to the properties
                                properties->push_back(std::to_string(item_number));

                                // Object complete, add to cyLevel
                                createStruct(obj_name, properties);

                                // Delete property list and create a new one
                                delete properties;
                                properties = new std::vector<std::string>();

                                // Avoid repetition (normally takes 3 loops until there's a new item)
                                waitForNewItem = true;
                                item_number++;
                                std::cout << "New Item" << std::endl;
                            }

                        } else {
                            // Extract new values
                            waitForNewItem = false;

                            // FIND VALUE
                            if (level[ptr] != '[' && level[ptr] != ']' && level[ptr] != ' ' && level[ptr] != ',')
                            {
                                size_t value_end;

                                // Is it a color value?
                                if (level[ptr] == 'c')
                                {
                                    // Find end of color value
                                    value_end = level.find(')', ptr) + 1;

                                } else {
                                    // Find when they end (Next , or ])
                                    size_t value_end_1 = level.find(',', ptr);
                                    size_t value_end_2 = level.find(']', ptr);
                                    value_end          = (value_end_1 > value_end_2) ? value_end_2 : value_end_1;
                                }

                                std::string value  = level.substr(ptr, value_end-ptr);
                                ptr = value_end - 1;

                                std::cout << value << std::endl;
                                properties->push_back(value);
                            }
                        }

                        ptr++;

                    }

                }
            }
        }

        ptr++;
    }

    // Generate Level Meshes
    this->generateWorldMesh();
}

/*template <typename OS>
void WorldSpawn::createStruct(OS* object_struct, std::vector<property_type>& value_types,
                              std::vector<std::string>* property_list);
{

}*/

void WorldSpawn::createStruct(const std::string& obj_name, std::vector<std::string>* properties)
{
    if (obj_name == "Floor")
    {
        float f_height = stof(properties->at(11))*HEIGHT;

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((stof(properties->at(0))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(1)) - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((stof(properties->at(2))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(3)) - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((stof(properties->at(4))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(5)) - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((stof(properties->at(6))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(7)) - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);
        f1.textureID  = 1;

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = 1;

        polys.push_back(f1);
        polys.push_back(f2);
    }
}

void WorldSpawn::generateWorldMesh()
{
    for (auto poly : this->polys)
    {
        polygon_mesh p_m;

        std::vector<GLfloat> p, t, n;
        std::vector<GLuint>  i;

        p.insert(p.end(), {poly.vertex[1].x, poly.vertex[1].y, poly.vertex[1].z});
        p.insert(p.end(), {poly.vertex[2].x, poly.vertex[2].y, poly.vertex[2].z});
        p.insert(p.end(), {poly.vertex[3].x, poly.vertex[3].y, poly.vertex[3].z});
        p.insert(p.end(), {poly.vertex[0].x, poly.vertex[0].y, poly.vertex[0].z});

        i = {0, 1, 3, 1, 2, 3};

        t.insert(t.end(), {poly.vertex[1].x*TEXTURE_SIZE, poly.vertex[1].z*TEXTURE_SIZE});
        t.insert(t.end(), {poly.vertex[2].x*TEXTURE_SIZE, poly.vertex[2].z*TEXTURE_SIZE});
        t.insert(t.end(), {poly.vertex[3].x*TEXTURE_SIZE, poly.vertex[3].z*TEXTURE_SIZE});
        t.insert(t.end(), {poly.vertex[0].x*TEXTURE_SIZE, poly.vertex[0].z*TEXTURE_SIZE});

        for (int iterator = 0; iterator < 8; iterator++)
            n.insert(n.end(), {poly.normal.x, poly.normal.y, poly.normal.z});

        p_m.meshID = Loader::loadToVAO(p, i, t, n);
        poly_meshes.push_back(p_m);
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

    /*glBindVertexArray(mesh->getVaoID());
    glDrawElements(GL_TRIANGLES, mesh->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);*/

    for (auto poly : poly_meshes)
    {
        glBindVertexArray(poly.meshID->getVaoID());
        glDrawElements(GL_TRIANGLES, poly.meshID->getVertexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

}

void WorldSpawn::update(const float dt)
{
    this->position  = glm::vec3(0, -.6f, 0);
    //this->rotation  = sf::Vector3f(0, this->rotation.y + 0.015, this->rotation.z + 0.01);
    this->scale     = 20.0f;

    createTransformationMatrix();
}
