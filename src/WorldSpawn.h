#ifndef WORLDSPAWN_H
#define WORLDSPAWN_H

#include <Entity.h>
#include <iostream>

#include "StaticShader.h"
#include "OBJLoader.h"

const int WORLD_SIZE = 400 / 2;

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

class WorldSpawn : public Entity
{
private:
    std::vector<cyFloor> floors;

    StaticShader* shader;

    void generateWorldMesh();
    void renderWorld();

public:
    WorldSpawn(StaticShader* sh);

    void draw();
    void update(const float dt);
};

#endif // WORLDSPAWN_H
