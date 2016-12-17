#include "CYPrimitives.h"

using namespace CYLevelLoader;

namespace CYLevelLoader
{
    LevelTextures* level_textures = new LevelTextures();
}

void CYLevelLoader::addFloor(float x1, float y1, float x2, float y2, float x3, float y3,
                             float x4, float y4, int level, const std::string& texture1, const std::string& texture2,
                             std::vector<p2t_ground>* floors)
{
    // Set up
    p2t_ground floor;
    floor.level = level;

    if (texture1[0] == 'c') {
        floor.floorTexture = CY_COLOR;
        floor.floorColors  = extractColor(texture1);
    } else {
        floor.floorTexture = CYLevelLoader::level_textures->getPlatformTexture(stoi(texture1));
    }

    if (texture2[0] == 'c') {
        floor.floorTexture = CY_COLOR;
        floor.floorColors  = extractColor(texture2);
    } else {
        floor.floorTexture = CYLevelLoader::level_textures->getPlatformTexture(stoi(texture2));
    }

    // Initialise variables
    std::vector<p2t::Point*> ground;
    std::vector<p2t::Triangle*> triangles;

    // Create main polygon for the ground
    ground.push_back(new p2t::Point(x1,  y1));
    ground.push_back(new p2t::Point(x2,  y2));
    ground.push_back(new p2t::Point(x3,  y3));
    ground.push_back(new p2t::Point(x4,  y4));
    floor.quad = ground;

    floors->push_back(std::move(floor));
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
    f1.triwall     = tri;

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

    polys->push_back(f1);
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
