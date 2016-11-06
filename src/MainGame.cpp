#include "MainGame.h"

MainGame::MainGame()
{
    // Init libraries / window
    initWindow();
    initGL();

    mainLoop();
}

void MainGame::mainLoop()
{
    StaticShader* sshader = new StaticShader();

    Cube cube(this->loader, sshader);

    while (this->window->isOpen())
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glClearColor(2.f/255, 119.f/255, 189.f/255, 1.0f);
sshader->use();
        cube.draw();

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

    this->window = new sf::Window(sf::VideoMode(WIDTH, HEIGHT), "BagCraft",
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

    return true;
}

////// UPDATE FUNCTIoNS //////

void MainGame::updateWindow()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch(event.type)
        {
        case sf::Event::Closed :
            window->close();
            break;

        case sf::Event::Resized :
            window->setSize({event.size.width, event.size.height});
            glViewport(0, 0, event.size.width, event.size.height);
            break;
        }
    }
}

////// DESTRUCTOR //////

MainGame::~MainGame()
{
    delete this->window;
}
