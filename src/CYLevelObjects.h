#ifndef CYLEVELOBJECTS_H
#define CYLEVELOBJECTS_H

#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "LevelTextures.h"

namespace CYLevelLoader
{
    // Constants
    const float WORLD_SIZE    = 400 / 2;
    const float HEIGHT        = 0.05f;
    const float TEXTURE_SIZE  = 20.f;

    // Level Textures
    extern LevelTextures* level_textures;

    // Polygon struct w/ properties
    struct polygon
    {
        glm::vec3   vertex[4];
        glm::vec3   normal;
        texture_id  textureID;
        std::vector<GLfloat> colors = {255, 255, 255};

        bool    vertical = false;
        float   v_length, v_x, v_y;

        bool    is_ramp  = false;
        int     triwall  = 0;
    };

    // Create new Object with certain amount of properties
    extern std::vector<std::string>* properties;
    void addNewObject(const std::string& obj_name, std::vector<std::string>* obj_properties,
                      std::vector<polygon>* polys);

    // Primitive Objects
    void addFloor(float x1, float y1, float x2, float y2, float x3, float y3,
                  float x4, float y4, int level, const std::string& texture1,
                  const std::string& texture2, std::vector<polygon>* polys);

    void addHorizontalQuad(float x1, float y1, float x2, float y2, float x3, float y3,
                          float x4, float y4, float o_height, int tri,
                          const std::string& texture, std::vector<polygon>* polys);

    void addPillar(float x, float y, bool angled, int level, int z_idx, int size,
                   const std::string& texture, std::vector<polygon>* polys);

    void addRamp(float x, float y, sf::Vector2f width, sf::Vector2f length,
                 float min_height, float max_height, bool upsidedown,
                 const std::string& texture, std::vector<polygon>* polys);

    void addVerticalQuad(float x1, float y1, float x2, float y2, float min_height,
                         float max_height, int tri, bool front_side,
                         const std::string& texture, std::vector<polygon>* polys);

    // Extract Color Property
    std::vector<GLfloat> extractColor(const std::string& data);
};

// Quick conversions
inline int         ptoi(int id) { return stoi(CYLevelLoader::properties->at(id)); }
inline float       ptof(int id) { return stof(CYLevelLoader::properties->at(id)); }
inline std::string ptos(int id) { return CYLevelLoader::properties->at(id); }

#endif // CYLEVELOBJECTS_H
