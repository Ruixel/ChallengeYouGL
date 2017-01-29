#include "World.h"

World::World()
{}

void World::initWorld(sf::RenderWindow& window)
{
    this->m_window = &window;
    this->m_camera.init(window);

    setupCameraUniforms();

    // Preload fonts
    if (!font_GoldenRatio.loadFromFile("dat/GoldenRatio.otf"))
        std::cout << "Error loading GoldenRatio font" << std::endl;

    // Set up PostFX
    m_postfx.init(m_window->getSize().x, m_window->getSize().y);

    // GUI Text
    text_MouseControl.setFont(font_GoldenRatio);
    text_MouseControl.setString("MOUSE CONTROL OFF - PRESS 'T'");
    text_MouseControl.setCharacterSize(18);
    text_MouseControl.setFillColor(sf::Color(255, 184, 16, 255));
    text_MouseControl.setPosition(window.getSize().x - 307, 5);

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

    //insertEntity(std::make_unique<SkyDome>(m_staticShader));
    //insertEntity(std::make_unique<WorldSpawn>("dat/maps/Misc.cy", m_staticShader, &m_camera, &m_postfx));
}

void World::updateWorld(float deltaTime)
{
    float fps = 1.f / deltaTime;
    static sf::Clock c;
    if (c.getElapsedTime().asSeconds() > 0.4)
    {
        text_FPS.setString("FPS: " + std::to_string(round(fps)));
        c.restart();
    }

    m_camera.update(deltaTime);

    for (auto& m_entity : worldEntities)
    {
        m_entity->update(deltaTime);
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

    // Bind Back to the default window & draw main FBO on quad
    m_postfx.renderScene(quadVao);

    // GUI
    m_window->pushGLStates();

    if (!m_camera.getToggle())
        m_window->draw(text_MouseControl);

    for (auto& m_gui : world_GUI)
    {
        m_window->draw(*m_gui);
    }

    m_window->draw(text_FPS);

    m_window->popGLStates();

}

////////////////////////

void World::insertEntity(std::unique_ptr<Entity> entity)
{
    worldEntities.push_back(std::move(entity));
}

void World::insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget)
{
    world_GUI.push_back(std::move(gui_widget));
}

Camera* World::getCamera()
{
    return &m_camera;
}

void World::resizeGUI(int width, int height)
{
    for (auto& m_gui : world_GUI)
    {
        m_gui->setParentSize(width, height);
    }
}

void World::setupCameraUniforms()
{
    m_staticShader.use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix(90);
    m_staticShader.loadProjectionMatrix(pMatrix);
    //m_staticShader.enableLighting(true);
    m_staticShader.stop();
}
