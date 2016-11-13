#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Entity.h"
#include "Cube.h"
#include "Camera.h"
#include "StaticShader.h"

class World
{
private:
    std::list<Entity*> worldEntities;

    Camera m_camera;
    StaticShader* m_staticShader;

    Cube* m_cube;

public:
    World();
    ~World();

    void initWorld();
    void updateWorld();
    void renderWorld();
};

#endif // WORLD_H
