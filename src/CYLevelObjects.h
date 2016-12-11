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
                      std::vector<polygon>* polys);

    // Properties list
    extern std::vector<std::string>* properties;
};

// Quick conversions
inline int         ptoi(int id) { return stoi(CYLevelLoader::properties->at(id)); }
inline float       ptof(int id) { return stof(CYLevelLoader::properties->at(id)); }
inline std::string ptos(int id) { return CYLevelLoader::properties->at(id); }

#endif // CYLEVELOBJECTS_H
