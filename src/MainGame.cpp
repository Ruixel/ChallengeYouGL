#include "MainGame.h"

MainGame::MainGame()
{
    // Init libraries / window
    initWindow();
    initGL();

    m_world.initWorld(this->window);
    mainLoop();
}

void MainGame::mainLoop()
{
    while (this->window->isOpen())
    {
        m_world.updateWorld();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor(2.f/255, 119.f/255, 189.f/255, 1.0f);

        m_world.renderWorld();

        window->display();
        this->updateWindow();
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
    this->window->setVerticalSyncEnabled(true);

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

    glCullFace(GL_BACK);

    return true;
}

////// UPDATE FUNCTIoNS //////

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
}
