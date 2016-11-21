#ifndef WORLD_H
#define WORLD_H

#include <list>

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
    sf::Window* m_window;

public:
    World();
    ~World();

    void initWorld(sf::Window* window);
    void updateWorld();
    void renderWorld();

    void insertEntity(Entity* entity);
};

#endif // WORLD_H
