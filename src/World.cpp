#include "World.h"

World::World()
{}

void World::initWorld()
{
    m_staticShader  = new StaticShader();
    m_cube          = new Cube(m_staticShader);
}

void World::updateWorld()
{
    m_cube->update(0.f);
}

void World::renderWorld()
{
    m_cube->draw();
}

World::~World()
{
    delete m_staticShader;
    delete m_cube;
}
