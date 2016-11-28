#include "World.h"

World::World()
{}

void World::initWorld(sf::RenderWindow* window)
{
    this->m_window = window;
    this->m_camera.init(window);
    m_staticShader  = new StaticShader();

    m_staticShader->use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix(1.6f);
    m_staticShader->loadProjectionMatrix(pMatrix);
    m_staticShader->stop();

    // Preload fonts
    if (!font_GoldenRatio.loadFromFile("dat/GoldenRatio.otf"))
        std::cout << "Error loading GoldenRatio font" << std::endl;

    // GUI Text
    text_MouseControl.setFont(font_GoldenRatio);
    text_MouseControl.setString("MOUSE CONTROL OFF - PRESS 'T'");
    text_MouseControl.setCharacterSize(18);
    text_MouseControl.setColor(sf::Color(255, 184, 16, 255));
    text_MouseControl.setPosition(717, 5);

    for (int i = 0; i < 20; i++)
    {
        Cube* m_cube = new Cube(m_staticShader);
        m_cube->setPosition(glm::vec3(0, 0, -5));

        insertEntity(m_cube);
    }

    WorldSpawn* ws = new WorldSpawn("dat/CGMarioPlat.cy", m_staticShader);
    insertEntity(ws);
}

void World::updateWorld()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::T)
                m_camera.toggleLockMouse();
            break;

        case sf::Event::Closed :
            m_window->close();
            break;

        case sf::Event::Resized :
            m_window->setSize({event.size.width, event.size.height});
            glViewport(0, 0, event.size.width, event.size.height);
            break;

        default:
            break;
        }
    }

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

    m_window->pushGLStates();

    if (!m_camera.getToggle())
        m_window->draw(text_MouseControl);

    m_window->popGLStates();

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
