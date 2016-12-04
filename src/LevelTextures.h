#ifndef LEVELTEXTURES_H
#define LEVELTEXTURES_H

#include <map>

#include "Loader.h"

enum texture_id
{
    CY_COLOR                    = 0,
    CY_GRASS                    = 1,
    CY_STUCCO                   = 2,
    CY_BRICK                    = 3,
    CY_STONE                    = 4,
    CY_WOOD                     = 5,
    CY_HAPPY                    = 6,
    CY_EGYPT                    = 7,
    CY_GLASS                    = 8,
    CY_BARK                     = 9,
    CY_SCIFI                    = 10,
    CY_TILE                     = 11,
    CY_ROCK                     = 13,
    CY_PARQUET                  = 14,
    CY_BARS                     = 16,
    CY_BOOKS                    = 17,

    CY_UNASSIGNED               = 256
};

class LevelTextures
{
private:
    std::map<texture_id, int> texture_hashmap;

    void loadTextures();

public:
    LevelTextures();

    texture_id getPlatformTexture(int id);
    texture_id getWallTexture(int id);

    void bindTexture(texture_id id);
};

#endif // LEVELTEXTURES_H
