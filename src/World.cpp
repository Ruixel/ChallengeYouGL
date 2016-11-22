#include "World.h"

World::World()
{}

void World::initWorld(sf::Window* window)
{
    this->m_window = window;
    this->m_camera.init(window);
    m_staticShader  = new StaticShader();

    m_staticShader->use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix(1.6f);
    m_staticShader->loadProjectionMatrix(pMatrix);
    m_staticShader->stop();

    for (int i = 0; i < 20; i++)
    {
        Cube* m_cube = new Cube(m_staticShader);
        m_cube->setPosition(glm::vec3(0, 0, -5));

        insertEntity(m_cube);
    }

    WorldSpawn* ws = new WorldSpawn(m_staticShader);
    insertEntity(ws);
}

void World::updateWorld()
{
    m_camera.update();

    for (auto m_entity : worldEntities)
    {
        m_entity->update(0.f);
    }
}

void World::renderWorld()
{
    m_staticShader->use();
    m_staticShader->loadViewMatrix(m_camera);

    for (auto m_entity : worldEntities)
    {
        m_entity->draw();
    }

    m_staticShader->stop();
}

World::~World()
{
    delete m_staticShader;

    for (auto m_entity : worldEntities)
        delete m_entity;
}

////////////////////////

void World::insertEntity(Entity* entity)
{
    worldEntities.push_back(entity);
}
