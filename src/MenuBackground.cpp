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
    sky_dome = std::make_unique<SkyDome>(m_staticShader);

    // Set up lights
    m_lights[1].Color = glm::vec3(0.55f, 0.55f, 0.25f);
    m_lights[1].Position = glm::vec3(5, 50, -60);

    m_lights[2].Color = glm::vec3(0.55f, 0.55f, 0.25f);
    m_lights[2].Position = glm::vec3(-5, 50, -60);

    //m_lights[0].Color = glm::vec3(0.2f, 0.4f, 0.5f);
    //m_lights[0].Position = glm::vec3(400, 800, 0);

    m_lights[0].Color = glm::vec3(0.8f, 1.0f, 1.0f);
    m_lights[0].Position = glm::vec3(400, 800, 0);
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
    // Geometry Shader
    m_geometryShader.use();
    glm::mat4 pMatrix = m_camera.generateProjectionMatrix(45);
    m_geometryShader.loadProjectionMatrix(pMatrix);
    m_geometryShader.stop();

    // Static Shader
    m_staticShader.use();
    m_staticShader.loadProjectionMatrix(pMatrix);
    m_staticShader.stop();
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
    // Ambient Shadows
    // DEPTH MAP PASS
    m_shadowmap.configureDepthPass();
    m_shadowmap.setLightViewMatrix(glm::vec3(50, 100, -40), glm::vec3(0, 70, -50));
    w_spawn->drawForDepthShader(m_shadowmap.getDepthShader());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, m_window->getSize().x, m_window->getSize().y);

    /*m_screenShader.use();
    glBindVertexArray(quadVao->getVaoID());
    glActiveTexture(GL_TEXTURE0);
    m_shadowmap.bindDepthTexture();
    glDrawElements(GL_TRIANGLES, quadVao->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);*/

    // GEOMETRY PASS
    // Set up
    m_gbuffer.bindForWriting();

    glDepthMask(GL_TRUE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //glEnable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    // Render Geometry
    this->renderGeometry();

    // Render to screen
    m_gbuffer.unbindFramebuffer();
    m_gbuffer.bindForReading();

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Stencil test
    /*glEnable(GL_DEPTH_TEST);
    glStencilMask(0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);*/

    /*

    sf::Vector2u windowSize = this->m_window->getSize();
    GLsizei HalfWidth  = 1280/2.0f;
    GLsizei HalfHeight = 720/2.0f;

    m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    glBlitFramebuffer(0, 0, windowSize.x, windowSize.y, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_ALBEDO);
    glBlitFramebuffer(0, 0, windowSize.x, windowSize.y, 0, HalfHeight, HalfWidth, windowSize.y,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);

    m_gbuffer.setReadBuffer(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glBlitFramebuffer(0, 0, windowSize.x, windowSize.y, HalfWidth, HalfHeight, windowSize.x, windowSize.y,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);*/

    /*m_screenShader.use();
    glBindVertexArray(quadVao->getVaoID());
    m_gbuffer.bindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glDrawElements(GL_TRIANGLES, quadVao->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);*/

    // LIGHTING PASS
    // Set up
    //glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    // Set up textures
    this->m_LightingPassShader.use();
    glActiveTexture(GL_TEXTURE0);
    m_gbuffer.bindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_POSITION);
    glActiveTexture(GL_TEXTURE1);
    m_gbuffer.bindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glActiveTexture(GL_TEXTURE2);
    m_gbuffer.bindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_ALBEDO);
    glActiveTexture(GL_TEXTURE3);
    m_shadowmap.bindDepthTexture();

    this->renderLights();
    this->m_LightingPassShader.setViewPosition(m_camera);
    this->m_LightingPassShader.setLightSpaceMatrix(m_shadowmap.getLightSpaceMatrix());

    glBindVertexArray(quadVao->getVaoID());
    //m_gbuffer.bindTexture(GBuffer::GBUFFER_TEXTURE_TYPE_NORMAL);
    glDrawElements(GL_TRIANGLES, quadVao->getVertexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Stencil disable
    glStencilMask(0x00);

    // Forward Render Sky Dome
    m_staticShader.use();

    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glDisable(GL_DEPTH_TEST);

    m_staticShader.loadViewMatrix(m_camera);
    //sky_dome->draw();
    m_staticShader.stop();

    // GUI
    m_window->pushGLStates();

    for (auto& m_gui : this->m_GUI)
    {
        m_window->draw(*m_gui);
    }

    m_window->popGLStates();
}

void MenuBackground::renderGeometry()
{
    //

    m_geometryShader.use();
    m_geometryShader.loadViewMatrix(m_camera);

    w_spawn->draw();

    m_geometryShader.stop();

    glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

}

void MenuBackground::renderLights()
{
    for (int i = 0; i < m_lights.size(); i++ )
    {
        m_LightingPassShader.setVec3LightSetting(i, "Position", m_lights[i].Position);
        m_LightingPassShader.setVec3LightSetting(i, "Color", m_lights[i].Color);

        m_LightingPassShader.setFloatLightSetting(i, "Linear", m_lights[i].linear);
        m_LightingPassShader.setFloatLightSetting(i, "Quadratic", m_lights[i].quadratic);
    }
}

CinematicCamera* MenuBackground::getCamera()
{
    return &m_camera;
}
