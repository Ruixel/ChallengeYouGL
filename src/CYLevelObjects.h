#ifndef CYLEVELOBJECTS_H
#define CYLEVELOBJECTS_H

#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "CYPrimitives.h"

namespace CYLevelLoader
{
    // Create new Object with certain amount of properties
    void addNewObject(const std::string& obj_name, std::vector<std::string>* obj_properties,
                      objVector* obj_v);

    // Properties list
    extern std::vector<std::string>* properties;

    // Create CY Objects
    // Wall: [[x_size, y_size, x_start, y_start], [texture1, texture2, z_idx], level]
    void createWall(float x_size, float y_size, float x, float y, int level, int z_idx,
                    const std::string& texture1, const std::string& texture2,
                    std::vector<polygon>* polys);

    // Plat: [[x, y], [size, texture, z_idx], level]
    void createPlat(float x, float y, int size, int level, int z_idx,
                    const std::string& texture, std::vector<polygon>* polys);

    // Pillar: [[x, y], [angle, texture, size, z_idx], level]
    void createPillar(float x, float y, int angled, float size, int level, int z_idx,
                      const std::string& texture, std::vector<polygon>* polys);

    // Ramp: [[x, y], [direction, texture], level]
    void createRamp(float x, float y, int direction, int level,
                    const std::string& texture, std::vector<polygon>* polys);

    // Hole: [[x, y], [size], level]
    void createHole(float x, float y, int size, int level, std::vector<polygon>* polys);
};

// Quick conversions
inline int         ptoi(int id) { return stoi(CYLevelLoader::properties->at(id)); }
inline float       ptof(int id) { return stof(CYLevelLoader::properties->at(id)); }
inline std::string ptos(int id) { return CYLevelLoader::properties->at(id); }

#endif // CYLEVELOBJECTS_H
