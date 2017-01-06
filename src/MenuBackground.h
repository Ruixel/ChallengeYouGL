#ifndef MENUBACKGROUND_H
#define MENUBACKGROUND_H

#include "WorldSpawn.h"
#include "CinematicCamera.h"
#include "StaticShader.h"
#include "SkyDome.h"
#include "gui/Widget.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    const double M_PI = 3.1415926535;
#endif // defined

class MenuBackground
{
private:
    CinematicCamera m_camera;
    StaticShader m_staticShader;
    sf::RenderWindow* m_window;

    std::unique_ptr<WorldSpawn> w_spawn;
    std::unique_ptr<SkyDome>    sky_dome;

    std::vector<std::unique_ptr<GUI::Widget>> m_GUI;
    void setupGUI();

public:
    MenuBackground();

    void initMenu(sf::RenderWindow& m_window);
    void updateMenu(float deltaTime);
    void renderMenu();

    void setupCameraUniforms();
    CinematicCamera* getCamera();

    void insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget);
    void resizeGUI(int width, int height);
};

#endif // MENUBACKGROUND_H
