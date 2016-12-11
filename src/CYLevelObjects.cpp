#include "CYLevelObjects.h"

using namespace CYLevelLoader;

namespace CYLevelLoader
{
    LevelTextures* level_textures = new LevelTextures();
    std::vector<std::string>* properties = new std::vector<std::string>();
}

void CYLevelLoader::addNewObject(const std::string& obj_name, std::vector<std::string>* obj_properties,
                                  std::vector<polygon>* polys)
{
    properties = obj_properties;
    if (obj_name == "Floor")
    {
        if (properties->at(9) == "2")
            return;

        addFloor(ptof(0),  ptof(1),  ptof(2), ptof(3), ptof(4), ptof(5), ptof(6), ptof(7),
                 ptoi(11), ptos(8), ptos(10), polys);

    }

    if (obj_name == "Plat")
    {
        float p_height = ptoi(5) + ((ptoi(4) - 1.f) / 4) + 0.001f;

        int size       = ptoi(2);
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        int x_min      = ptof(0) - size*5;
        int x_max      = ptof(0) + size*5;
        int y_min      = ptof(1) - size*5;
        int y_max      = ptof(1) + size*5;

        addHorizontalQuad(x_min, y_max, x_max, y_max, x_max, y_min, x_min, y_min, p_height, 0, ptos(3), polys);
        addHorizontalQuad(x_min, y_min, x_max, y_min, x_max, y_max, x_min, y_max, p_height, 0, ptos(3), polys);
    }

    if (obj_name == "DiaPlat")
    {
        float p_height = ptof(5) + ((ptoi(4) - 1.f) / 4) + 0.001f;

        int size       = ptoi(2);
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        size *= 5;

        int x_min      = stoi(properties->at(0)) - size;
        int x_max      = stoi(properties->at(0)) + size;
        int y_min      = stoi(properties->at(1)) - size;
        int y_max      = stoi(properties->at(1)) + size;

        addHorizontalQuad(x_min+size, y_max, x_max, y_max-size, x_max-size, y_min, x_min, y_min+size, p_height, 0, ptos(3), polys);
        addHorizontalQuad(x_min, y_min+size, x_max-size, y_min, x_max, y_max-size, x_min+size, y_max, p_height, 0, ptos(3), polys);
    }

    if (obj_name == "TriPlat")
    {
        float p_height = ptof(6) + ((ptoi(5) - 1.f) / 4) + 0.001f;

        int size       = ptoi(2);
        switch (size)
        {
            case 3:  size = 4; break;
            case 4:  size = 8; break;
            default: size = size;
        }

        size *= 5;

        int first_tri, second_tri;
        switch(ptoi(4))
        {
            case 1: first_tri = 1; second_tri = 2; break;
            case 2: first_tri = 3; second_tri = 4; break;
            case 3: first_tri = 2; second_tri = 1; break;
            case 4: first_tri = 4; second_tri = 3; break;
        }

        int x_min      = ptoi(0) - size;
        int x_max      = ptoi(0) + size;
        int y_min      = ptoi(1) - size;
        int y_max      = ptoi(1) + size;

        addHorizontalQuad(x_min, y_max, x_max, y_max, x_max, y_min, x_min, y_min, p_height, first_tri,  ptos(3), polys);
        addHorizontalQuad(x_min, y_min, x_max, y_min, x_max, y_max, x_min, y_max, p_height, second_tri, ptos(3), polys);
    }

    if (obj_name == "Ramp")
    {
        float min_height = ptof(4);
        float max_height = (ptof(4)+1);

        int x_1          = ptof(0);
        int y_1          = ptof(1);

        sf::Vector2f length, width;
        int direction    = ptoi(2);
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

        addRamp(x_1, y_1, width, length, min_height, max_height, false, ptos(3), polys);
        addRamp(x_1, y_1, width, length, min_height, max_height, true, ptos(3), polys);
    }

    if (obj_name == "walls")
    {
        float height = ptof(7);
        float height_max, height_min;

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
            case 10: height_max = height + 3/4.f;  height_min = height + 1/4.f; break;

            default: height_max = height + 4/4.f;  height_min = height; break;
        }

        float x_1 = ptof(2);
        float x_2 = x_1 + ptof(0);
        float y_1 = ptof(3);
        float y_2 = y_1 + ptof(1);

        addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 0, true, ptos(4), polys);
        addVerticalQuad(x_1, y_1, x_2, y_2, height_min, height_max, 0, false, ptos(5), polys);
    }
}

void CYLevelLoader::addFloor(float x1, float y1, float x2, float y2, float x3, float y3,
                              float x4, float y4, int level, const std::string& texture1, const std::string& texture2,
                              std::vector<polygon>* polys)
{
    addHorizontalQuad(x1, y1, x2, y2, x3, y3, x4, y4, level, 0, texture1, polys);
    addHorizontalQuad(x4, y4, x3, y3, x2, y2, x1, y1, level, 0, texture2, polys);
}

void CYLevelLoader::addHorizontalQuad(float x1, float y1, float x2, float y2, float x3, float y3,
                          float x4, float y4, float o_height, int tri,
                          const std::string& texture, std::vector<polygon>* polys)
{
    // Quick scaling
    o_height *= HEIGHT;

    polygon f1;
    f1.vertex[0]  = glm::vec3((x1   - 200)  / WORLD_SIZE, o_height, (y1 - 200)  / WORLD_SIZE);
    f1.vertex[1]  = glm::vec3((x2   - 200)  / WORLD_SIZE, o_height, (y2 - 200)  / WORLD_SIZE);
    f1.vertex[2]  = glm::vec3((x3   - 200)  / WORLD_SIZE, o_height, (y3 - 200)  / WORLD_SIZE);
    f1.vertex[3]  = glm::vec3((x4   - 200)  / WORLD_SIZE, o_height, (y4 - 200)  / WORLD_SIZE);
    f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);
    f1.triwall    = tri;

    if (texture[0] == 'c') {
        f1.textureID = CY_COLOR;
        f1.colors    = CYLevelLoader::extractColor(texture);
    } else {
        f1.textureID = CYLevelLoader::level_textures->getPlatformTexture(stoi(texture));
    }
    polys->push_back(f1);
}

void CYLevelLoader::addRamp(float x, float y, sf::Vector2f width, sf::Vector2f length,
                            float min_height, float max_height, bool upsidedown,
                            const std::string& texture, std::vector<polygon>* polys)
{
    // Quick scaling
    min_height *= HEIGHT;
    max_height *= HEIGHT;

    polygon f1;

    if (!upsidedown) {
        f1.vertex[1]  = glm::vec3((x + length.x            - 200)  / WORLD_SIZE, max_height, (y                      - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x + width.x + length.x  - 200)  / WORLD_SIZE, max_height, (y + width.y            - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x + width.x             - 200)  / WORLD_SIZE, min_height, (y + width.y + length.y - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x                       - 200)  / WORLD_SIZE, min_height, (y + length.y           - 200)  / WORLD_SIZE);
    } else {
        f1.vertex[2]  = glm::vec3((x + length.x            - 200)  / WORLD_SIZE, max_height, (y                      - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((x + width.x + length.x  - 200)  / WORLD_SIZE, max_height, (y + width.y            - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x + width.x             - 200)  / WORLD_SIZE, min_height, (y + width.y + length.y - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x                       - 200)  / WORLD_SIZE, min_height, (y + length.y           - 200)  / WORLD_SIZE);
    }

    f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);
    f1.vertical   = true;
    f1.v_length   = sqrt(pow(width.x, 2) + pow(width.y, 2));
    f1.v_x        = 2;
    f1.is_ramp    = true;

    if (texture[0] == 'c') {
        f1.textureID = CY_COLOR;
        f1.colors    = CYLevelLoader::extractColor(texture);
    } else {
        f1.textureID = CYLevelLoader::level_textures->getPlatformTexture(stoi(texture));
    }
    polys->push_back(f1);
}

// VERTICAL QUADRILATERAL
void CYLevelLoader::addVerticalQuad(float x_1, float y_1, float x_2, float y_2, float min_height,
                                    float max_height, int tri, bool front_side, const std::string& texture,
                                    std::vector<polygon>* polys)
{
    max_height *= HEIGHT; min_height *= HEIGHT;

    polygon f1;
    f1.vertical    = true;
    f1.v_length    = sqrt(pow(y_2-y_1, 2) + pow(x_2-x_1, 2));
    //std::cout << "x length: " << x_2-x_1 << ", y length: " << y_2-y_1 << std::endl;
    //std::cout << "Length: " << f1.v_length << std::endl;
    f1.v_x         = x_2;

    if (front_side) {
        f1.vertex[1]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, max_height, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[2]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, max_height, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, min_height, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, min_height, (y_1 - 200)  / WORLD_SIZE);
    } else {
        f1.vertex[2]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, max_height, (y_1 - 200)  / WORLD_SIZE);
        f1.vertex[1]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, max_height, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[0]  = glm::vec3((x_2   - 200)  / WORLD_SIZE, min_height, (y_2 - 200)  / WORLD_SIZE);
        f1.vertex[3]  = glm::vec3((x_1   - 200)  / WORLD_SIZE, min_height, (y_1 - 200)  / WORLD_SIZE);
    }
    f1.normal     = glm::cross(f1.vertex[2] - f1.vertex[1], f1.vertex[3] - f1.vertex[1]);

    if (texture[0] == 'c') {
        f1.textureID = CY_COLOR;
        f1.colors    = extractColor(texture);
    } else {
        f1.textureID = CYLevelLoader::level_textures->getWallTexture(stoi(texture));
    }

    polys->push_back(std::move(f1));
}

std::vector<GLfloat> CYLevelLoader::extractColor(const std::string& data)
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
