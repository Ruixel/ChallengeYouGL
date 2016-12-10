#ifndef CYLEVELLOADER_H
#define CYLEVELLOADER_H

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>
#include <math.h>

#include "Loader.h"

#include "CYLevelObjects.h"

namespace CYLevelLoader
{
    // Converted from the polygon struct
    // Contains the information for the 3D space
    // TODO: Right now it uses quads instead of triangular polygons
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

    // Chunk of a single texture (VAO & TextureID)
    struct static_world_chunk
    {
        std::unique_ptr<RawModel>   meshID;
        texture_id                  textureID;
    };

    // ChallengeYou Level
    struct cyLevel
    {
        std::string name, author, levels, version;
        std::vector<static_world_chunk> chunks;
    };

    // Main functions
    cyLevel loadFromWebsite(int gameNumber);
    cyLevel loadFromFile(const char* levelPath);

    std::vector<polygon> loadContentsIntoChunks(const std::string& level, cyLevel& level_objs);

    std::vector<polygon_mesh> convertPolygonsIntoMeshInfo(const std::vector<polygon>& polys);
    std::vector<static_world_chunk> generateWorldMeshes(std::vector<polygon_mesh>& poly_meshes);
};

#endif // CYLEVELLOADER_H
