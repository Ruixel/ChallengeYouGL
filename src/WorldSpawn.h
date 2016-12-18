#ifndef WORLDSPAWN_H
#define WORLDSPAWN_H

#include "Entity.h"

#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include <math.h>

#include "Camera.h"
#include "Loader.h"
#include "StaticShader.h"
#include "OBJLoader.h"
#include "LevelTextures.h"
#include "CYLevelLoader.h"
#include "PostFX.h"

using namespace CYLevelLoader;

class WorldSpawn : public Entity
{
private:
    std::map<int, int> texture_hashmap;

    LevelTextures level_textures;

    cyLevel level_objs;

    StaticShader* shader;
    Camera* m_camera;

    void createStruct(const std::string& obj_name, std::vector<std::string>* properties);

    std::vector<GLfloat> extractColor(const std::string& data);

    void generateWorldMesh();
    void renderWorld();

public:
    WorldSpawn(const char* levelPath, StaticShader& sh, Camera* camera, PostFX* postfx);

    void draw();
    void update(const float dt);
};

#endif // WORLDSPAWN_H
