#ifndef WORLDSPAWN_H
#define WORLDSPAWN_H

#include <Entity.h>

#include <string>
#include <fstream>
#include <iostream>

#include "StaticShader.h"
#include "OBJLoader.h"

const float WORLD_SIZE = 400 / 2;
const float HEIGHT     = 0.2f;

// PRIMITIVES

struct cyQuad
{ glm::vec3 v1, v2, v3, v4; };

struct cyTexture
{ int texture; glm::vec3 color; };

// OBJECTS

struct cyFloor
{
    cyQuad coordinates;
    cyTexture topSurface;
    cyTexture bottomSurface;
};

struct cyLevel
{
    std::string name, author, levels, version;
    std::vector<cyFloor> level_floors;
};

enum class property_type
{
    CY_QUAD, CY_BOOL, CY_TEXTURE
};

class WorldSpawn : public Entity
{
private:
    std::vector<cyFloor> floors;
    cyLevel level_objs;

    StaticShader* shader;

    //template <typename OS>
    //void createStruct(OS* object_struct, std::vector<property_type>& value_types,
    //                  std::vector<std::string>* property_list);

    void createStruct(const std::string& obj_name, std::vector<std::string>* properties);

    void generateWorldMesh();
    void renderWorld();

public:
    WorldSpawn(const char* levelPath, StaticShader* sh);

    void draw();
    void update(const float dt);
};

#endif // WORLDSPAWN_H
