#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Cube.h"
#include "WorldSpawn.h"
#include "Camera.h"
#include "StaticShader.h"

class World
{
private:
    std::list<Entity*> worldEntities;

    Camera m_camera;
    StaticShader* m_staticShader;
    sf::RenderWindow* m_window;

    sf::Font font_GoldenRatio;
    sf::Text text_MouseControl;
    sf::Text text_FPS;

public:
    World();
    ~World();

    void initWorld(sf::RenderWindow* window);
    void updateWorld(float deltaTime);
    void renderWorld();

    void insertEntity(Entity* entity);
};

#endif // WORLD_H
