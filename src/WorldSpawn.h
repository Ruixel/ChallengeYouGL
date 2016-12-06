#ifndef WORLDSPAWN_H
#define WORLDSPAWN_H

#include "Entity.h"

#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <math.h>

#include "Loader.h"
#include "StaticShader.h"
#include "OBJLoader.h"
#include "LevelTextures.h"

const float WORLD_SIZE    = 400 / 2;
const float HEIGHT        = 0.05f;
const float TEXTURE_SIZE  = 20.f;

// OBJECTS
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

struct polygon_mesh
{
    //std::unique_ptr<RawModel>   meshID;

    std::vector<GLfloat> p, t, n, c;
    std::vector<GLuint>  i;

    texture_id                  textureID;

    bool operator < (const polygon_mesh& a) const
    {
        return textureID < a.textureID;
    }
};

struct translucent_polygon
{
    std::unique_ptr<RawModel>   meshID;
    texture_id                  textureID;

    glm::vec3 midpoint;
};

// Temporary Optimization
struct static_world_chunk
{
    std::unique_ptr<RawModel>   meshID;
    texture_id                  textureID;
};

struct cyLevel
{
    std::string name, author, levels, version;
    //std::vector<cyFloor> level_floors;
};

class WorldSpawn : public Entity
{
private:
    std::vector<polygon>             polys;
    std::vector<polygon_mesh>        poly_meshes;
    std::vector<translucent_polygon> trans_polys;
    std::vector<static_world_chunk>  s_w_chunks;

    std::map<int, int> texture_hashmap;

    cyLevel level_objs;

    LevelTextures level_textures;

    StaticShader* shader;

    void createStruct(const std::string& obj_name, std::vector<std::string>* properties);

    std::vector<GLfloat> extractColor(const std::string& data);

    void generateWorldMesh();
    void renderWorld();

public:
    WorldSpawn(const char* levelPath, StaticShader& sh);

    void draw();
    void update(const float dt);
};

#endif // WORLDSPAWN_H
