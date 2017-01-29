#include "MenuBackground.h"

MenuBackground::MenuBackground()
: m_screenShader("shaders/basic_fbo.vert", "shaders/basic_fbo.frag")
{}

void MenuBackground::initMenu(sf::RenderWindow& window)
{
    m_window = &window;
    m_camera.init(window);
    m_camera.toggleLockMouse();

    setupCameraUniforms();
    setupGUI();

    m_gbuffer.init(window.getSize().x, window.getSize().y);

    quadVao = Loader::loadToVAO(bag::quadVertices, bag::quadIndices, bag::quadTexCoods);

    w_spawn  = std::make_unique<WorldSpawn>("dat/maps/Misc.cy", m_geometryShader, &m_camera, nullptr);
    sky_dome = std::make_unique<SkyDome>(m_geometryShader);
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

    std::unique_ptr<GUI::Image> title = std::make_unique<GUI::Image>(1280, 720, "dat/img/title.png");
    title->setSize(sf::FloatRect(0, 843, 0, 164));
    title->setPos(sf::FloatRect(0, 5, 0, 55));
    insertGUIWidget(std::move(title));
}

void MenuBackground::updateMenu(float deltaTime)
{
    sky_dome->update(deltaTime);
    w_spawn->update(deltaTime);
    m_camera.update(deltaTime);
}

void MenuBackground::insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget)
{
    m_GUI.push_back(std::move(gui_widget));
}

void MenuBackground::setupCameraUniforms()
{
    m_geometryShader.use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix(45);
    m_geometryShader.loadProjectionMatrix(pMatrix);
    m_geometryShader.stop();
}

/*int n = 10;
float aperture = 0.05f;

void MenuBackground::renderMenu()
{

    //m_staticShader.loadViewMatrix(m_camera);

    // get camera vectors
    glm::vec3 right = m_camera.get_right();
    glm::vec3 p_up  = m_camera.get_p_up(right);

    for (int i = 0; i < n; i++)
    {
        m_staticShader.use();
        glm::vec3 bokeh = right * cosf(i * 20 * M_PI / n) + p_up * sinf(i * 20 * M_PI / n);
        m_staticShader.loadViewMatrix(m_camera, aperture, bokeh, p_up);

        w_spawn->draw();
        sky_dome->draw();

        m_staticShader.stop();

        // GUI
        m_window->pushGLStates();

        for (auto& m_gui : this->m_GUI)
        {
            m_window->draw(*m_gui);
        }

        m_window->popGLStates();

        // Accumulation Buffer
        glAccum(i ? GL_ACCUM : GL_LOAD, 1.0 / n);
    }


}*/

void MenuBackground::renderMenu()
{
    m_gbuffer.bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glClearColor(2.f/255, 119.f/255, 189.f/255, 1.0f);
    this->renderGeometry();
    m_gbuffer.unbindFramebuffer();

    m_screenShader.use();
    glBindVertexArray(quadVao->getVaoID());
    m_gbuffer.bindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_ALBEDO);
    glDrawElements(GL_TRIANGLES, quadVao->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void MenuBackground::renderGeometry()
{
    m_geometryShader.use();
    m_geometryShader.loadViewMatrix(m_camera);

    w_spawn->draw();
    sky_dome->draw();

    m_geometryShader.stop();

    /*/ GUI
    m_window->pushGLStates();

    for (auto& m_gui : this->m_GUI)
    {
        m_window->draw(*m_gui);
    }

    m_window->popGLStates();*/


}

CinematicCamera* MenuBackground::getCamera()
{
    return &m_camera;
}
