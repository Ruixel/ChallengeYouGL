#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Cube.h"
#include "SkyDome.h"
#include "WorldSpawn.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include "StaticShader.h"
#include "GBuffer.h"
#include "BasicShader.h"
#include "PostFX.h"
#include "gui/Widget.h"

class World
{
private:
    std::vector<std::unique_ptr<Entity>> worldEntities;
    std::vector<std::unique_ptr<GUI::Widget>> world_GUI;

    Camera m_camera;
    StaticShader m_staticShader;
    sf::RenderWindow* m_window;

    sf::Font font_GoldenRatio;
    sf::Text text_MouseControl;
    sf::Text text_FPS;

    PostFX m_postfx;
    std::unique_ptr<RawModel> quadVao;

public:
    World();

    void initWorld(sf::RenderWindow& window);
    void updateWorld(float deltaTime);
    void renderWorld();

    void insertEntity(std::unique_ptr<Entity> entity);
    void insertGUIWidget(std::unique_ptr<GUI::Widget> gui_widget);
    Camera* getCamera();
    void setupCameraUniforms();

    void resizeGUI(int width, int height);
};

#endif // WORLD_H
