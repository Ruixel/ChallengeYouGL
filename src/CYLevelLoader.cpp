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

    objVector obj_v = CYLevelLoader::loadContentsIntoChunks(level, game_level);
    std::vector<polygon_mesh> poly_meshes = CYLevelLoader::convertPolygonsIntoMeshInfo(obj_v);

    // Sort the polygons via texture
    std::sort(poly_meshes.begin(), poly_meshes.end());

    game_level.chunks = generateWorldMeshes(poly_meshes);

    return game_level;
}

cyLevel CYLevelLoader::loadFromWebsite(int gameNumber)
{
    // Load file
    std::string level;

    // Setup connection
    sf::Http http;
    http.setHost("http://www.challengeyou.com/");
    std::cout << "Initialising connection to www.challengeyou.com" << std::endl;

    // Setup request
    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    std::string uri = "ChallengeFiles/Maze/Maze" + std::to_string(gameNumber);
    request.setUri(uri);
    std::cout << "Sending request to game number #" << gameNumber << std::endl;

    // Send GET Request
    sf::Http::Response response = http.sendRequest(request);

    // Check if it's a success
    if (response.getStatus() != 200)
    {
        std::cout << "FAILED, exited with status: " << response.getStatus() << std::endl;
    }

    // Copy contents into level string
    level = response.getBody();

    cyLevel game_level;

    objVector obj_v = CYLevelLoader::loadContentsIntoChunks(level, game_level);
    std::vector<polygon_mesh> poly_meshes = CYLevelLoader::convertPolygonsIntoMeshInfo(obj_v);

    // Sort the polygons via texture
    std::sort(poly_meshes.begin(), poly_meshes.end());

    game_level.chunks = generateWorldMeshes(poly_meshes);

    return game_level;
}

objVector CYLevelLoader::loadContentsIntoChunks(const std::string& level, cyLevel& level_objs)
{
    // Object to be returned
    objVector obj_v;

    // Initialise points
    obj_v.polys  = new std::vector<polygon>();
    obj_v.floors = new std::vector<p2t_ground>();
    obj_v.holes  = new std::vector<p2t_quad>();

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
                                    addNewObject(obj_name, properties, &obj_v);

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

    return obj_v;
}
std::vector<polygon_mesh> CYLevelLoader::convertPolygonsIntoMeshInfo(objVector& obj_v)
{
    std::vector<polygon_mesh> poly_meshes;

    // Sort through the holes to reduce load time
    std::sort(obj_v.holes->begin(), obj_v.holes->end());

    int hole_number = 0;
    for (auto& ground : *obj_v.floors)
    {
        std::vector<p2t::Triangle*> triangles;
        p2t::CDT* cdt = new p2t::CDT(ground.quad);

        // Add holes
        for (int it = 0; it < obj_v.holes->size(); it++)
        {
            if ((*obj_v.holes)[it].level != ground.level)
                continue;

            cdt->AddHole((*obj_v.holes)[it].quad);
        }

        cdt->Triangulate();
        triangles = cdt->GetTriangles();

        for (int i = 0; i < triangles.size(); i++)
        {
            polygon_mesh p_m;

            p2t::Triangle& t = *triangles[i];
            p2t::Point&   p1 = *t.GetPoint(0);
            p2t::Point&   p2 = *t.GetPoint(1);
            p2t::Point&   p3 = *t.GetPoint(2);

            p_m.i = {1, 0, 2};

            float g_height = ground.level * HEIGHT;
            glm::vec3 pos1 = glm::vec3((p1.x - 200)  / WORLD_SIZE, g_height, (p1.y - 200)  / WORLD_SIZE);
            glm::vec3 pos2 = glm::vec3((p2.x - 200)  / WORLD_SIZE, g_height, (p2.y - 200)  / WORLD_SIZE);
            glm::vec3 pos3 = glm::vec3((p3.x - 200)  / WORLD_SIZE, g_height, (p3.y - 200)  / WORLD_SIZE);
            glm::vec3 norm = glm::cross(pos3 - pos1, pos2 - pos1);

            p_m.p.insert(p_m.p.end(), {pos1.x, pos1.y, pos1.z});
            p_m.p.insert(p_m.p.end(), {pos2.x, pos2.y, pos2.z});
            p_m.p.insert(p_m.p.end(), {pos3.x, pos3.y, pos3.z});

            sf::Vector2f tSize = CYLevelLoader::level_textures->getTextureSize(ground.floorTexture);

            p_m.t.insert(p_m.t.end(), {pos1.x*TEXTURE_SIZE * tSize.x, pos1.z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {pos2.x*TEXTURE_SIZE * tSize.x, pos2.z*TEXTURE_SIZE * tSize.y});
            p_m.t.insert(p_m.t.end(), {pos3.x*TEXTURE_SIZE * tSize.x, pos3.z*TEXTURE_SIZE * tSize.y});

            p_m.textureID = ground.floorTexture;

            for (int it = 0; it < 3; it++)
                p_m.c.insert(p_m.c.end(), {ground.floorColors[0], ground.floorColors[1], ground.floorColors[2]});

            for (int it = 0; it < 3; it++)
                p_m.n.insert(p_m.n.end(), {norm.x, norm.y, norm.z});

            p_m.index_count = 3;

            // Copy
            polygon_mesh p_m2   = p_m;
            p_m2.i              = {2, 0, 1};
            glm::vec3 norm2     = glm::cross(pos2 - pos1, pos3 - pos1);
            p_m2.textureID      = ground.ceilingTexture;

            p_m2.c.clear();
            for (int it = 0; it < 3; it++)
                p_m2.c.insert(p_m2.c.end(), {ground.ceilingColors[0], ground.ceilingColors[1], ground.ceilingColors[2]});

            p_m2.n.clear();
            for (int it = 0; it < 3; it++)
                p_m2.n.insert(p_m2.n.end(), {norm2.x, norm2.y, norm2.z});

            // Push back
            poly_meshes.push_back(std::move(p_m));
            poly_meshes.push_back(std::move(p_m2));
        }

    }

    for (auto& poly : *obj_v.polys)
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

            float x_2d, start_x;
            x_2d = poly.v_length;
            x_2d = (x_2d - 200) / WORLD_SIZE;
            start_x = (0 - 200) / WORLD_SIZE;

            if (poly.is_ramp)
            {
                tSize.x *= 1.f; tSize.y *= 1.6f;
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

        i_counter += poly.index_count;

    }

    world_chunk->meshID    = Loader::loadToVAO(p, i, t, n, c);
    world_chunk->textureID = previous_texture;
    s_w_chunks.push_back(std::move(*world_chunk));
    delete world_chunk;

    return s_w_chunks;
}
