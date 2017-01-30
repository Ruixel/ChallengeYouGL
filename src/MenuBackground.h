#ifndef MENUBACKGROUND_H
#define MENUBACKGROUND_H

#include "WorldSpawn.h"
#include "CinematicCamera.h"
#include "StaticShader.h"
#include "gStaticShader.h"
#include "LightingPass.h"
#include "GBuffer.h"
#include "SkyDome.h"
#include "gui/Widget.h"
#include "gui/Image.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const double M_PI = 3.1415926535;
#endif // defined

struct Light
{
    glm::vec3 Position = glm::vec3(0,0,0);
    glm::vec3 Color = glm::vec3(0,0,0);

    float linear = 0.7f;
    float quadratic = 1.8f;
};

class MenuBackground
{
private:
    CinematicCamera m_camera;
    // StaticShader m_staticShader;
    gStaticShader m_geometryShader;
    BasicShader   m_screenShader;
    LightingPass  m_LightingPassShader;

    sf::RenderWindow* m_window;

    std::unique_ptr<WorldSpawn> w_spawn;
    std::unique_ptr<SkyDome>    sky_dome;

    GBuffer m_gbuffer;
    std::unique_ptr<RawModel> quadVao;

    std::array<Light, 32> m_lights;

    std::vector<std::unique_ptr<GUI::Widget>> m_GUI;
    void setupGUI();

public:
    MenuBackground();

    void initMenu(sf::RenderWindow& m_window);
    void updateMenu(float deltaTime);
    void renderMenu();

    void setupCameraUniforms();
    CinematicCamera* getCamera();

    void renderGeometry();
    void renderLights();

    void insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget);
    void resizeGUI(int width, int height);
};

#endif // MENUBACKGROUND_H
