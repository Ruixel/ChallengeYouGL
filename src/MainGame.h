#ifndef MAINGAME_H
#define MAINGAME_H

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stack>

#include "StaticShader.h"
#include "Cube.h"
#include "Loader.h"
#include "GLError.h"
#include "World.h"
#include "State_Base.h"
#include "State_Playing.h"

class MainGame
{
private:
    const int WIDTH      = 1280;
    const int HEIGHT     = 720;
    const int FRAME_RATE = 120;
    const int ANTI_ALIAS = 4;

    std::stack<State::State_Base*> states;

    sf::RenderWindow* window;

    std::unique_ptr<World> m_world;

    bool initGL();
    void initWindow();

    void updateWindow();

    sf::Clock clock;

public:
    MainGame();
    ~MainGame();

    // STATE FUNCTIONS //
    void pushState(State::State_Base* state);
    void popState();
    void changeState(State::State_Base* state);
    State::State_Base* peekState();

    void mainLoop();
};

#endif // MAINGAME_H
