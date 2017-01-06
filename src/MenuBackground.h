#ifndef MENUBACKGROUND_H
#define MENUBACKGROUND_H

#include "WorldSpawn.h"
#include "Camera.h"
#include "StaticShader.h"
#include "SkyDome.h"
#include "gui/Widget.h"

class MenuBackground
{
private:
    Camera m_camera;
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
    void insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget);

    void resizeGUI(int width, int height);
};

#endif // MENUBACKGROUND_H
