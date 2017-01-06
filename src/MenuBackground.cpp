#include "MenuBackground.h"

MenuBackground::MenuBackground()
{}

void MenuBackground::initMenu(sf::RenderWindow& window)
{
    m_window = &window;
    m_camera.init(window);

    setupCameraUniforms();
    setupGUI();

    w_spawn  = std::make_unique<WorldSpawn>("dat/maps/Misc.cy", m_staticShader, &m_camera, nullptr);
    sky_dome = std::make_unique<SkyDome>(m_staticShader);
}

void MenuBackground::setupGUI()
{
    std::unique_ptr<GUI::Widget> test_box = std::make_unique<GUI::Widget>(1280, 720);
    test_box->setSize(sf::FloatRect(1, 0, 0, 60));
    test_box->setPos(sf::FloatRect(0, 0, 0, -10));
    test_box->setColor(sf::Color(0, 0, 0, 255));
    insertGUIWidget(std::move(test_box));

    std::unique_ptr<GUI::Widget> test_box2 = std::make_unique<GUI::Widget>(1280, 720);
    test_box2->setSize(sf::FloatRect(1, 0, 0, 60));
    test_box2->setPos(sf::FloatRect(0, 0, 1, -50));
    test_box2->setColor(sf::Color(0, 0, 0, 255));
    insertGUIWidget(std::move(test_box2));
}

void MenuBackground::updateMenu(float deltaTime)
{
    sky_dome->update(deltaTime);
    m_camera.update(deltaTime);
}

void MenuBackground::insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget)
{
    m_GUI.push_back(std::move(gui_widget));
}

void MenuBackground::setupCameraUniforms()
{
    m_staticShader.use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix();
    m_staticShader.loadProjectionMatrix(pMatrix);
    m_staticShader.stop();
}

void MenuBackground::renderMenu()
{
    m_staticShader.use();
    m_staticShader.loadViewMatrix(m_camera);

    sky_dome->draw();
    w_spawn->draw();
}
