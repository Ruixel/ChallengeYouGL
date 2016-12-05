#include "WorldSpawn.h"

WorldSpawn::WorldSpawn(const char* levelPath, StaticShader& sh)
//:   Entity(Loader::loadToVAO(v, i, t, v), Loader::loadTexture("iceman.jpg"))
:   shader(&sh)
{
    // Load file
    std::string level;

    std::ifstream level_string_buffer;
    level_string_buffer.exceptions(std::ifstream::badbit);

    // Variables & Iterators
    unsigned ptr = 0;
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

                if (!std::isupper(obj_name[0]) && obj_name != "walls" && obj_name != "begin")
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
                    std::vector<std::string>* properties = new std::vector<std::string>();
                    int item_bracket = 3;

                    if (obj_name == "Floor" or obj_name == "walls")
                        item_bracket = 4;

                    while (bracket > end_bracket)
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
                                if (obj_name == "Floor")
                                    properties->push_back(std::to_string(item_number));

                                // Object complete, create entity
                                if (properties->size() != 0)
                                    createStruct(obj_name, properties);

                                // Delete property list and create a new one
                                delete properties;
                                properties = new std::vector<std::string>();

                                // Avoid repetition (normally takes 3 loops until there's a new item)
                                waitForNewItem = true;
                                item_number++;

                                //std::cout << "New Item" << std::endl;
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

                                //std::cout << value << std::endl;
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

void WorldSpawn::createStruct(const std::string& obj_name, std::vector<std::string>* properties)
{
    if (obj_name == "Floor")
    {
        if (properties->at(9) == "2")
            return;

        float f_height = stof(properties->at(11))*HEIGHT;

        texture_id texID1 = CY_COLOR;
        if ((properties->at(8))[0] != 'c')
            texID1 = level_textures.getPlatformTexture(stoi(properties->at(8)));

        texture_id texID2 = CY_COLOR;
        if ((properties->at(10))[0] != 'c')
            texID2 = level_textures.getPlatformTexture(stoi(properties->at(10)));

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((stof(properties->at(0))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(1)) - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((stof(properties->at(2))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(3)) - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((stof(properties->at(4))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(5)) - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((stof(properties->at(6))   - 200)  / WORLD_SIZE, f_height, (stof(properties->at(7)) - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);
        f1.textureID  = texID1;

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = texID2;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "Plat")
    {
        float p_height = stof(properties->at(5))*HEIGHT + ((stof(properties->at(4)) - 1.f) / 4)*HEIGHT;

        int size       = stoi(properties->at(2));
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        int x_min      = stoi(properties->at(0)) - size*5;
        int x_max      = stoi(properties->at(0)) + size*5;
        int y_min      = stoi(properties->at(1)) - size*5;
        int y_max      = stoi(properties->at(1)) + size*5;

        polygon f1, f2;
        f1.vertex[0]  = glm::vec3((x_min   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((x_max   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_max - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_max   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_min   - 200)  / WORLD_SIZE, p_height+(0.001*HEIGHT), (y_min - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(3)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "Ramp")
    {
        polygon f1, f2;

        float min_height = stof(properties->at(4))*HEIGHT;
        float max_height = (stof(properties->at(4))+1)*HEIGHT;

        int x_1          = stoi(properties->at(0));
        int y_1          = stoi(properties->at(1));

        sf::Vector2f length, width;
        int direction    = stoi(properties->at(2));
        switch (direction)
        {
            // Vertical & Horizontal Ramps
            case 1: width  = {10, 0};
                    length = {0, 20};
                    x_1    -= 5;
                    break;
            case 2: width  = {10, 0};
                    length = {0, -20};
                    x_1    -= 5;
                    break;
            case 3: width  = {0, 10};
                    length = {-20, 0};
                    x_1    += 20;
                    y_1    -= 5;
                    break;
            case 4: width  = {0, 10};
                    length = {20, 0};
                    x_1    -= 20;
                    y_1    -= 5;
                    break;

            // Diagonal Ramps
            case 5: width  = {10, -10};
                    length = {-15, 15};
                    x_1    += 10;
                    y_1    += 5;
                    break;
            case 6: width  = {10, 10};
                    length = {-15, -15};
                    x_1    += 10;
                    y_1    -= 5;
                    break;
            case 7: width  = {-10, 10};
                    length = {15, -15};
                    x_1    -= 10;
                    y_1    -= 5;
                    break;
            case 8: width  = {10, 10};
                    length = {15, 15};
                    x_1    -= 20;
                    y_1    -= 5;
                    break;
        }

        f1.vertical    = true;
        f1.v_length    = sqrt(pow(length.x, 2) + pow(length.y, 2));

        f1.vertex[1]  = glm::vec3((x_1 + length.x            - 200)  / WORLD_SIZE, max_height, (y_1                      - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_1 + width.x + length.x  - 200)  / WORLD_SIZE, max_height, (y_1 + width.y            - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_1 + width.x             - 200)  / WORLD_SIZE, min_height, (y_1 + width.y + length.y - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1                       - 200)  / WORLD_SIZE, min_height, (y_1 + length.y           - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getPlatformTexture(stoi(properties->at(3)));
        }

        f1.is_ramp = true;
        f2.is_ramp = true;

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;
        f2.vertical   = true;
        f2.v_length   = f1.v_length;

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "walls")
    {
        polygon f1, f2;
        float height = stof(properties->at(7));
        float height_max, height_min;

        //std::cout << "Z_IND: " << stoi(properties->at(6)) << std::endl;

        switch(stoi(properties->at(6)))
        {
            case 2:  height_max = height + 3/4.f;  height_min = height; break;
            case 3:  height_max = height + 2/4.f;  height_min = height; break;
            case 4:  height_max = height + 1/4.f;  height_min = height; break;

            case 5:  height_max = height + 2/4.f;  height_min = height + 1/4.f; break;
            case 6:  height_max = height + 3/4.f;  height_min = height + 2/4.f; break;
            case 7:  height_max = height + 4/4.f;  height_min = height + 3/4.f; break;

            case 8:  height_max = height + 4/4.f;  height_min = height + 2/4.f; break;
            case 9:  height_max = height + 4/4.f;  height_min = height + 1/4.f; break;
            case 10:  height_max = height + 3/4.f;  height_min = height + 1/4.f; break;

            default: height_max = height + 4/4.f;  height_min = height; break;
        }

        height_max *= HEIGHT; height_min *= HEIGHT;

        int x_1 = stof(properties->at(2));
        int x_2 = x_1 + stof(properties->at(0));
        int y_1 = stof(properties->at(3));
        int y_2 = y_1 + stof(properties->at(1));

        f1.vertical    = true;
        f1.v_length    = sqrt(pow(x_2-x_1, 2) + pow(y_2-y_1, 2));
        f1.v_x = x_1;

        f1.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(4))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(4));
        } else {
            f1.textureID = level_textures.getWallTexture(stoi(properties->at(4)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;
        f2.vertical   = true;
        f2.v_length   = f1.v_length;
        f2.v_x        = x_1;

        if ((properties->at(5))[0] == 'c') {
            f2.textureID = CY_COLOR;
            f2.colors    = extractColor(properties->at(5));
        } else {
            f2.textureID = level_textures.getWallTexture(stoi(properties->at(5)));
        }

        polys.push_back(f1);
        polys.push_back(f2);
    }

    if (obj_name == "TriWall")
    {
        polygon f1, f2;
        float height = stof(properties->at(5));
        float height_max = height       *HEIGHT;
        float height_min = (height + 1) *HEIGHT;

        int x_1 = stof(properties->at(0));
        int y_1 = stof(properties->at(1));
        int x_2, y_2;

        int dir = stoi(properties->at(4));
        switch (dir)
        {
            case 1: x_2 = x_1;  y_2 = y_1 + 20;     break;
            case 2: x_2 = x_1;  y_2 = y_1 - 20;     break;
            case 3: x_2 = x_1 + 20;  y_2 = y_1;     break;
            case 4: x_2 = x_1 - 20;  y_2 = y_1;     break;

            case 5: x_2 = x_1 + 15;  y_2 = y_1 - 15;     break;
            case 6: x_2 = x_1 + 15;  y_2 = y_1 + 15;     break;
            case 7: x_2 = x_1 - 15;  y_2 = y_1 + 15;     break;
            case 8: x_2 = x_1 - 15;  y_2 = y_1 - 15;     break;
        }

        if (stoi(properties->at(2)) == 1) {
            f1.triwall = 1; f2.triwall = 2;
        } else {
            f1.triwall = 3; f2.triwall = 4;
        }

        f1.vertical    = true;
        f1.v_length    = sqrt(pow(x_2-x_1, 2) + pow(y_2-y_1, 2));
        f1.v_x = x_1;

        f1.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_max, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_max, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, height_min, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, height_min, (y_1 - 200)  / WORLD_SIZE);
        f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

        if ((properties->at(3))[0] == 'c') {
            f1.textureID = CY_COLOR;
            f1.colors    = extractColor(properties->at(3));
            f2.colors    = f1.colors;
        } else {
            f1.textureID = level_textures.getWallTexture(stoi(properties->at(3)));
        }

        f2.vertex[0]  = f1.vertex[3]; f2.vertex[1]  = f1.vertex[2];
        f2.vertex[2]  = f1.vertex[1]; f2.vertex[3]  = f1.vertex[0];
        f2.normal     = glm::cross(f2.vertex[2] - f2.vertex[1], f2.vertex[3] - f2.vertex[1]);
        f2.textureID  = f1.textureID;
        f2.vertical   = true;
        f2.v_length   = f1.v_length;
        f2.v_x        = x_1;

        f2.textureID = f1.textureID;

        polys.push_back(f1);
        polys.push_back(f2);
    }
}

std::vector<GLfloat> WorldSpawn::extractColor(const std::string& data)
{
    int ptr = 7;
    std::vector<GLfloat> color_vector;

    size_t value_end = data.find(',', ptr);
    color_vector.push_back(stof(data.substr(ptr, value_end-ptr)));
    ptr = value_end + 2;

    value_end = data.find(',', ptr);
    color_vector.push_back(stof(data.substr(ptr, value_end-ptr)));
    ptr = value_end + 2;

    value_end = data.find(')', ptr);
    color_vector.push_back(stof(data.substr(ptr, value_end-ptr)));

    //std::cout << "Colors: " << color_vector[0] << " | " << color_vector[1] << " | " << color_vector[2] << std::endl;

    return color_vector;
}

void WorldSpawn::generateWorldMesh()
{
    for (auto& poly : this->polys)
    {
        polygon_mesh p_m;

        //std::vector<GLfloat> p, t, n, c;
        //std::vector<GLuint>  i;

        p_m.p.insert(p_m.p.end(), {poly.vertex[1].x, poly.vertex[1].y, poly.vertex[1].z});
        p_m.p.insert(p_m.p.end(), {poly.vertex[2].x, poly.vertex[2].y, poly.vertex[2].z});
        p_m.p.insert(p_m.p.end(), {poly.vertex[3].x, poly.vertex[3].y, poly.vertex[3].z});
        p_m.p.insert(p_m.p.end(), {poly.vertex[0].x, poly.vertex[0].y, poly.vertex[0].z});

        // INDICES
        p_m.i = {0, 1, 3, 1, 2, 3};

        if (poly.triwall == 1)
            p_m.i = {0, 1, 3};

        if (poly.triwall == 2)
            p_m.i = {0, 1, 2};

        if (poly.triwall == 3)
            p_m.i = {1, 2, 3};

        if (poly.triwall == 4)
            p_m.i = {0, 2, 3};

        if (!poly.vertical) {
            sf::Vector2f tSize = level_textures.getTextureSize(poly.textureID);

            p_m.t.insert(p_m.t.end(), {poly.vertex[1].x*TEXTURE_SIZE * tSize.x, poly.vertex[1].z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.vertex[2].x*TEXTURE_SIZE * tSize.x, poly.vertex[2].z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.vertex[3].x*TEXTURE_SIZE * tSize.x, poly.vertex[3].z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.vertex[0].x*TEXTURE_SIZE * tSize.x, poly.vertex[0].z*TEXTURE_SIZE * tSize.y});

        } else {
            sf::Vector2f tSize = level_textures.getTextureSize(poly.textureID);

            float x_2d = poly.v_x + poly.v_length;
            x_2d = (x_2d - 200) / WORLD_SIZE;
            poly.v_x = (poly.v_x - 200) / WORLD_SIZE;

            if (poly.is_ramp)
            {
                tSize.x *= .8f; tSize.y *= 1.6f;
            }

            p_m.t.insert(p_m.t.end(), {poly.v_x*TEXTURE_SIZE * tSize.x, poly.vertex[1].y*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {x_2d*TEXTURE_SIZE     * tSize.x, poly.vertex[1].y*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {x_2d*TEXTURE_SIZE     * tSize.x, poly.vertex[0].y*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.v_x*TEXTURE_SIZE * tSize.x, poly.vertex[0].y*TEXTURE_SIZE * tSize.y});
        }

        for (int it = 0; it < 4; it++)
            p_m.c.insert(p_m.c.end(), {poly.colors[0], poly.colors[1], poly.colors[2]});

        for (int it = 0; it < 4; it++)
            p_m.n.insert(p_m.n.end(), {poly.normal.x, poly.normal.y, poly.normal.z});

        p_m.textureID = poly.textureID;
        //p_m.p = p; p_m.i = i; p_m.c = c; p_m.n = n; p_m.t = t;
        //p_m.meshID    = Loader::loadToVAO(p, i, t, n, c);

        poly_meshes.push_back(std::move(p_m));
    }

    //this->mesh = Loader::loadToVAO(vertices, indices, t_Coords, normals);

    // Sort the polygons via texture
    std::sort(poly_meshes.begin(), poly_meshes.end());

    // Place static primitives into a single VAO to reduce CPU overhead
    texture_id previous_texture = CY_UNASSIGNED;
    static_world_chunk* world_chunk;
    int i_counter = 0;
    std::vector<GLfloat> p, t, n, c;
    std::vector<GLuint>  i;
    for (auto& poly : poly_meshes)
    {
        if ((poly.textureID != previous_texture) && (previous_texture != CY_UNASSIGNED))
        {
            world_chunk->meshID    = Loader::loadToVAO(p, i, t, n, c);
            world_chunk->textureID = previous_texture;
            s_w_chunks.push_back(std::move(*world_chunk));

            delete world_chunk;
            world_chunk = new static_world_chunk;
            i_counter = 0;

            p.clear(); t.clear(); n.clear(); c.clear(); i.clear();

            world_chunk->textureID = poly.textureID;
            previous_texture = poly.textureID;

        } else {
            world_chunk = new static_world_chunk;
            previous_texture = poly.textureID;
        }

        n.insert(n.end(), poly.n.begin(), poly.n.end());
        c.insert(c.end(), poly.c.begin(), poly.c.end());
        p.insert(p.end(), poly.p.begin(), poly.p.end());
        t.insert(t.end(), poly.t.begin(), poly.t.end());

        for (GLuint index : poly.i)
            i.push_back(index + i_counter);

        i_counter += 4;
    }
    delete world_chunk;
}

void WorldSpawn::draw()
{
    shader->loadTransformationMatrix(transformationMatrix);

    glActiveTexture(GL_TEXTURE0);

    texture_id previous_texture = CY_UNASSIGNED;
    for (auto& chunk : s_w_chunks)
    {
        /*if (poly.textureID != previous_texture)
        {
            level_textures.bindTexture(poly.textureID);
            previous_texture = poly.textureID;
        }

        glBindVertexArray(poly.meshID->getVaoID());
        glDrawElements(GL_TRIANGLES, poly.meshID->getVertexCount(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);*/

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
