#include "World.h"

World::World()
: m_screenShader("shaders/basic_fbo.vert", "shaders/basic_fbo.frag")
{}

void World::initWorld(sf::RenderWindow& window)
{
    this->m_window = &window;
    this->m_camera.init(window);

    m_staticShader.use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix();
    m_staticShader.loadProjectionMatrix(pMatrix);
    m_staticShader.enableLighting(true);
    m_staticShader.stop();

    // Preload fonts
    if (!font_GoldenRatio.loadFromFile("dat/GoldenRatio.otf"))
        std::cout << "Error loading GoldenRatio font" << std::endl;

    // Set up G-Buffers
    m_postfx.init(m_window->getSize().x, m_window->getSize().y);

    // GUI Text
    text_MouseControl.setFont(font_GoldenRatio);
    text_MouseControl.setString("MOUSE CONTROL OFF - PRESS 'T'");
    text_MouseControl.setCharacterSize(18);
    text_MouseControl.setFillColor(sf::Color(255, 184, 16, 255));
    text_MouseControl.setPosition(717, 5);

    // FPS Text
    text_FPS.setFont(font_GoldenRatio);
    text_FPS.setString("FPS: 0");
    text_FPS.setCharacterSize(18);
    text_FPS.setFillColor(sf::Color(255, 184, 16, 255));
    text_FPS.setPosition(5, 5);

    for (int i = 0; i < 20; i++)
    {
        std::unique_ptr<Cube> cube = std::make_unique<Cube>(m_staticShader);
        cube->setPosition(glm::vec3(0, 0, -5));

        insertEntity(std::move(cube));
    }

    /* TEMP */
    quadVao = Loader::loadToVAO(bag::quadVertices, bag::quadIndices, bag::quadTexCoods);
    /* TEMP */

    insertEntity(std::make_unique<SkyDome>(m_staticShader));
    insertEntity(std::make_unique<WorldSpawn>("dat/maps/Misc.cy", m_staticShader, &m_camera));
}

void World::updateWorld(float deltaTime)
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

    float fps = 1.f / deltaTime;
    static sf::Clock c;
    if (c.getElapsedTime().asSeconds() > 0.4)
    {
        text_FPS.setString("FPS: " + std::to_string(round(fps)));
        c.restart();
    }

    m_camera.update();

    for (auto& m_entity : worldEntities)
    {
        m_entity->update(0.f);
    }
}

void World::renderWorld()
{
    /*
    m_staticShader.use();
    m_staticShader.loadViewMatrix(m_camera);

    for (auto& m_entity : worldEntities)
    {
        m_entity->draw();
    }

    m_staticShader.stop();

    m_window->pushGLStates();

    if (!m_camera.getToggle())
        m_window->draw(text_MouseControl);

    m_window->draw(text_FPS);

    m_window->popGLStates();*/

    // FBO Test
    // First Pass
    m_postfx.bindFramebuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(2.f/255, 119.f/255, 189.f/255, 1.0f);

    glEnable(GL_DEPTH_TEST);
    //glDisable(GL_BLEND);

    // Render
    m_staticShader.use();
    m_staticShader.loadViewMatrix(m_camera);

    for (auto& m_entity : worldEntities)
    {
        m_entity->draw();
    }

    m_staticShader.stop();

    m_window->pushGLStates();

    if (!m_camera.getToggle())
        m_window->draw(text_MouseControl);

    m_window->draw(text_FPS);

    m_window->popGLStates();

    // Bind Back to the default window & draw main FBO on quad
    m_postfx.unbindFramebuffer();
    glClearColor(0.f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    m_screenShader.use();
    glBindVertexArray(quadVao->getVaoID());
    m_postfx.bindTexture();
    glDrawElements(GL_TRIANGLES, quadVao->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

////////////////////////

void World::insertEntity(std::unique_ptr<Entity> entity)
{
    worldEntities.push_back(std::move(entity));
}
