#include "MainGame.h"

// STATE FUNCTION //
void MainGame::pushState(State::State_Base* state)
{
    this->states.push(state);
}

void MainGame::popState()
{
    delete this->states.top();
    this->states.pop();
}

void MainGame::changeState(State::State_Base* state)
{
    if (!this->states.empty())
        popState();

    pushState(state);
}

State::State_Base* MainGame::peekState()
{
    if (this->states.empty())
        return nullptr;

    return this->states.top();
}

// MAIN FUNCTION //

MainGame::MainGame()
{
    // Init libraries / window
    initWindow();
    initGL();

    this->pushState(new State::State_Menu(window));
}

int n = 6;
int i = 0;

void MainGame::mainLoop()
{
    auto currentTime    = 0.0f;
    auto deltaTime      = 0.0f;

    while (this->window->isOpen())
    {
        auto game_state = this->peekState();
        if (this->peekState() == nullptr)
            continue;

        peekState()->input();
        peekState()->update(deltaTime);
        peekState()->render();

        if (i==0)
            glAccum(GL_LOAD, 1.0 / n);
        else
            glAccum(GL_ACCUM, 1.0 / n);

        i++;

        if (i>=n)
        {
            i = 0;
            glAccum(GL_RETURN, 1.0);
            window->display();
            this->updateWindow();
        }

        currentTime = clock.restart().asSeconds();
        deltaTime = currentTime - 0;
    }
}

////// INIT FUNCTIONS //////

void MainGame::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel  = ANTI_ALIAS;
    settings.stencilBits        = 8;
    settings.depthBits          = 24;
    settings.majorVersion       = 3;
    settings.minorVersion       = 3;

    this->window = new sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "ChallengeYouGL",
                              sf::Style::Default, settings);

    this->window->setFramerateLimit(FRAME_RATE);
    this->window->setVerticalSyncEnabled(false);

    return;
}

bool MainGame::initGL()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return false;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCullFace(GL_BACK);

    return true;
}

////// UPDATE FUNCTIONS //////

void MainGame::updateWindow()
{
    /*sf::Event event;
    while (window->pollEvent(event))
    {
        switch(event.type)
        {

    }*/
}

////// DESTRUCTOR //////

MainGame::~MainGame()
{
    delete this->window;

    while (!this->states.empty())
        popState();
}
