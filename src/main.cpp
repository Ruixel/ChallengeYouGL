#include <iostream>

#include "MainGame.h"
#include "State_Playing.h"

int main()
{
    std::cout << "Initialising Game..." << std::endl;

    MainGame mainGame;
    mainGame.mainLoop();

    return 1;
}
