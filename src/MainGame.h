#ifndef MAINGAME_H
#define MAINGAME_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "StaticShader.h"
#include "Cube.h"
#include "Loader.h"
#include "GLError.h"
#include "World.h"

class MainGame
{
private:
    const int WIDTH      = 1024;
    const int HEIGHT     = 720;
    const int FRAME_RATE = 120;
    const int ANTI_ALIAS = 4;

    sf::RenderWindow* window;

    std::unique_ptr<World> m_world;

    bool initGL();
    void initWindow();

    void updateWindow();

    sf::Clock clock;

public:
    MainGame();
    ~MainGame();

    void mainLoop();
};

#endif // MAINGAME_H
