#ifndef LEVELTEXTURES_H
#define LEVELTEXTURES_H

#include <map>

#include "Loader.h"

enum class texture_id
{
    COLOR                    = 0,
    GRASS                    = 1,
    STUCCO                   = 2,
    BRICK                    = 3,
    STONE                    = 4,
    WOOD                     = 5,
    HAPPY                    = 6,
    EGYPT                    = 7,
    BARK                     = 9,
    SCIFI                    = 10,
    TILE                     = 11,
    ROCK                     = 13,
    PARQUET                  = 14,
    BOOKS                    = 17,

    // Translucent Textures
    BARS                     = 100,
    GLASS                    = 101,

    UNASSIGNED               = -1
};

class LevelTextures
{
private:
    std::map<texture_id, int>          texture_hashmap;
    std::map<texture_id, sf::Vector2f> texture_size;

    void loadTextures();

public:
    LevelTextures();

    texture_id getPlatformTexture(int id);
    texture_id getWallTexture(int id);

    const sf::Vector2f& getTextureSize(texture_id id);

    void bindTexture(texture_id id);
};

#endif // LEVELTEXTURES_H
