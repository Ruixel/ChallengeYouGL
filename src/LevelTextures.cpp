#include "LevelTextures.h"

void LevelTextures::loadTextures()
{
    // Load textures into heap memory
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_GRASS,   Loader::loadTexture("dat/img/grass.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_STUCCO,  Loader::loadTexture("dat/img/stucco.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_BRICK,   Loader::loadTexture("dat/img/bricks.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_STONE,   Loader::loadTexture("dat/img/stone.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_WOOD,    Loader::loadTexture("dat/img/wood.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_HAPPY,   Loader::loadTexture("dat/img/happy.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_EGYPT,   Loader::loadTexture("dat/img/egypt.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_GLASS,   Loader::loadTexture("dat/img/glass.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_BARK,    Loader::loadTexture("dat/img/bark.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_SCIFI,   Loader::loadTexture("dat/img/scifi.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_TILE,    Loader::loadTexture("dat/img/tile.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_ROCK,    Loader::loadTexture("dat/img/rock.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_BARS,    Loader::loadTexture("dat/img/bars.png")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_PARQUET, Loader::loadTexture("dat/img/parquet.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_BOOKS,   Loader::loadTexture("dat/img/bookshelf.jpg")));
    texture_hashmap.insert(std::make_pair<texture_id, int>(CY_COLOR,   Loader::loadTexture("dat/img/color.jpg")));

    // Texture Sizes
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_GRASS,   {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_STUCCO,  {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_BRICK,   {2.5f, 2.666f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_STONE,   {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_WOOD,    {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_HAPPY,   {4.f, 4.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_EGYPT,   {1.f, 2.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_GLASS,   {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_BARK,    {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_SCIFI,   {1.f, -1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_TILE,    {4.f, 5.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_BARS,    {3.5f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_BOOKS,   {1.f, 1.333f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_ROCK,    {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_PARQUET, {1.f, 1.f}));
    texture_size.insert(std::make_pair<texture_id, sf::Vector2f>(CY_COLOR,   {1.f, 1.f}));
}

LevelTextures::LevelTextures()
{
    this->loadTextures();
}

texture_id LevelTextures::getPlatformTexture(int id)
{
    switch (id) // PLATS
    {
        case 1: return  CY_GRASS;
        case 2: return  CY_STUCCO;
        case 3: return  CY_BRICK;
        case 4: return  CY_STONE;
        case 5: return  CY_WOOD;
        case 6: return  CY_HAPPY;
        case 7: return  CY_EGYPT;
        case 8: return  CY_GLASS;
        case 9: return  CY_BARK;
        case 10: return CY_SCIFI;
        case 11: return CY_TILE;
        case 13: return CY_ROCK;
        case 14: return CY_PARQUET;

        default: return CY_COLOR;
    }
}


texture_id LevelTextures::getWallTexture(int id)
{
    switch (id) // WALLS
    {
        case 1: return  CY_BRICK;
        case 2: return  CY_BARS;
        case 3: return  CY_STONE;
        case 4: return  CY_GRASS;
        case 5: return  CY_WOOD;
        case 6: return  CY_HAPPY;
        case 7: return  CY_EGYPT;
        case 8: return  CY_GLASS;
        case 9: return  CY_STUCCO;
        case 10: return CY_BARK;
        case 11: return CY_SCIFI;
        case 12: return CY_TILE;
        case 13: return CY_ROCK;
        case 14: return CY_BOOKS;
        case 16: return CY_PARQUET;

        default: return CY_COLOR;
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
