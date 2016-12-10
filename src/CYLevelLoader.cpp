#include "CYLevelLoader.h"

using namespace CYLevelLoader;

cyLevel CYLevelLoader::loadFromFile(const char* levelPath)
{
    // Load file
    std::string level;

    std::ifstream level_string_buffer;
    level_string_buffer.exceptions(std::ifstream::badbit);

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

    cyLevel game_level;

    std::vector<polygon> polys = CYLevelLoader::loadContentsIntoChunks(level, game_level);
    std::vector<polygon_mesh> poly_meshes = CYLevelLoader::convertPolygonsIntoMeshInfo(polys);

    // Sort the polygons via texture
    std::sort(poly_meshes.begin(), poly_meshes.end());

    game_level.chunks = generateWorldMeshes(poly_meshes);

    return game_level;
}

std::vector<polygon> CYLevelLoader::loadContentsIntoChunks(const std::string& level, cyLevel& level_objs)
{
    // Object to be returned
    std::vector<polygon> polys;

    // Variables & Iterators
    unsigned ptr = 0;
    int bracket = 0;
    std::string obj_type = "";

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
                        int item_bracket = 4;

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
                                    addNewObject(obj_name, properties, &polys);

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

    return polys;
}
std::vector<polygon_mesh> CYLevelLoader::convertPolygonsIntoMeshInfo(const std::vector<polygon>& polys)
{
    std::vector<polygon_mesh> poly_meshes;

    for (auto& poly : polys)
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
            sf::Vector2f tSize = CYLevelLoader::level_textures->getTextureSize(poly.textureID);

            p_m.t.insert(p_m.t.end(), {poly.vertex[1].x*TEXTURE_SIZE * tSize.x, poly.vertex[1].z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.vertex[2].x*TEXTURE_SIZE * tSize.x, poly.vertex[2].z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.vertex[3].x*TEXTURE_SIZE * tSize.x, poly.vertex[3].z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {poly.vertex[0].x*TEXTURE_SIZE * tSize.x, poly.vertex[0].z*TEXTURE_SIZE * tSize.y});

        } else {
            sf::Vector2f tSize = CYLevelLoader::level_textures->getTextureSize(poly.textureID);

            float x_2d = poly.v_x + poly.v_length;
            x_2d = (x_2d - 200) / WORLD_SIZE;
            int start_x = (poly.v_x - 200) / WORLD_SIZE;

            if (poly.is_ramp)
            {
                tSize.x *= .8f; tSize.y *= 1.6f;
            }

            p_m.t.insert(p_m.t.end(), {start_x*TEXTURE_SIZE * tSize.x, poly.vertex[1].y*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {x_2d*TEXTURE_SIZE     * tSize.x, poly.vertex[1].y*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {x_2d*TEXTURE_SIZE     * tSize.x, poly.vertex[0].y*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {start_x*TEXTURE_SIZE * tSize.x, poly.vertex[0].y*TEXTURE_SIZE * tSize.y});
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

    return poly_meshes;
}

std::vector<static_world_chunk> CYLevelLoader::generateWorldMeshes(std::vector<polygon_mesh>& poly_meshes)
{
    std::vector<static_world_chunk> s_w_chunks;

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

    world_chunk->meshID    = Loader::loadToVAO(p, i, t, n, c);
    world_chunk->textureID = previous_texture;
    s_w_chunks.push_back(std::move(*world_chunk));
    delete world_chunk;

    return s_w_chunks;
}
