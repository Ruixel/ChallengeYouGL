#include "LevelTextures.h"

void LevelTextures::loadTextures()
{
    // Load textures into heap memory
    texture_hashmap.insert(std::make_pair(texture_id::GRASS,   Loader::loadTexture("dat/img/grass.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::STUCCO,  Loader::loadTexture("dat/img/stucco.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::BRICK,   Loader::loadTexture("dat/img/bricks.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::STONE,   Loader::loadTexture("dat/img/stone.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::WOOD,    Loader::loadTexture("dat/img/wood.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::HAPPY,   Loader::loadTexture("dat/img/happy.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::EGYPT,   Loader::loadTexture("dat/img/egypt.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::GLASS,   Loader::loadTexture("dat/img/glass_alpha.png")));
    texture_hashmap.insert(std::make_pair(texture_id::BARK,    Loader::loadTexture("dat/img/bark.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::SCIFI,   Loader::loadTexture("dat/img/scifi.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::TILE,    Loader::loadTexture("dat/img/tile.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::ROCK,    Loader::loadTexture("dat/img/rock.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::BARS,    Loader::loadTexture("dat/img/bars.png")));
    texture_hashmap.insert(std::make_pair(texture_id::PARQUET, Loader::loadTexture("dat/img/parquet.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::BOOKS,   Loader::loadTexture("dat/img/bookshelf.jpg")));
    texture_hashmap.insert(std::make_pair(texture_id::COLOR,   Loader::loadTexture("dat/img/color.jpg")));

    // Texture Sizes
    texture_size.insert(std::make_pair(texture_id::GRASS,   sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::STUCCO,  sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::BRICK,   sf::Vector2f{2.5f, 2.666f}));
    texture_size.insert(std::make_pair(texture_id::STONE,   sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::WOOD,    sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::HAPPY,   sf::Vector2f{4.f, 4.f}));
    texture_size.insert(std::make_pair(texture_id::EGYPT,   sf::Vector2f{1.f, 2.f}));
    texture_size.insert(std::make_pair(texture_id::GLASS,   sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::BARK,    sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::SCIFI,   sf::Vector2f{1.f, -1.f}));
    texture_size.insert(std::make_pair(texture_id::TILE,    sf::Vector2f{4.f, 5.f}));
    texture_size.insert(std::make_pair(texture_id::BARS,    sf::Vector2f{3.5f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::BOOKS,   sf::Vector2f{1.f, 1.333f}));
    texture_size.insert(std::make_pair(texture_id::ROCK,    sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::PARQUET, sf::Vector2f{1.f, 1.f}));
    texture_size.insert(std::make_pair(texture_id::COLOR,   sf::Vector2f{2.f, 2.f}));
}

LevelTextures::LevelTextures()
{
    this->loadTextures();
}

texture_id LevelTextures::getPlatformTexture(int id)
{
    switch (id) // PLATS
    {
        case 1: return  texture_id::GRASS;
        case 2: return  texture_id::STUCCO;
        case 3: return  texture_id::BRICK;
        case 4: return  texture_id::STONE;
        case 5: return  texture_id::WOOD;
        case 6: return  texture_id::HAPPY;
        case 7: return  texture_id::EGYPT;
        case 8: return  texture_id::GLASS;
        case 9: return  texture_id::BARK;
        case 10: return texture_id::SCIFI;
        case 11: return texture_id::TILE;
        case 13: return texture_id::ROCK;
        case 14: return texture_id::PARQUET;

        default: return texture_id::COLOR;
    }
}


texture_id LevelTextures::getWallTexture(int id)
{
    switch (id) // WALLS
    {
        case 1: return  texture_id::BRICK;
        case 2: return  texture_id::BARS;
        case 3: return  texture_id::STONE;
        case 4: return  texture_id::GRASS;
        case 5: return  texture_id::WOOD;
        case 6: return  texture_id::HAPPY;
        case 7: return  texture_id::EGYPT;
        case 8: return  texture_id::GLASS;
        case 9: return  texture_id::STUCCO;
        case 10: return texture_id::BARK;
        case 11: return texture_id::SCIFI;
        case 12: return texture_id::TILE;
        case 13: return texture_id::ROCK;
        case 14: return texture_id::BOOKS;
        case 16: return texture_id::PARQUET;

        default: return texture_id::COLOR;
    }
}

const sf::Vector2f& LevelTextures::getTextureSize(texture_id id)
{
    return texture_size[id];
}

void LevelTextures::bindTexture(texture_id texID)
{
    glBindTexture(GL_TEXTURE_2D, texture_hashmap[texID]);
}
