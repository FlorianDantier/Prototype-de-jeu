#include <iostream>
#include "SDL_Game.h"


int main()
{

    SDL_Game sdl;
    if(sdl.init("Brain dead", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y))
    {
        while (sdl.getRunning())
        {
            sdl.render();
            sdl.handleEvents();
        }
    }
    else
    {
        std::cout<<"Fail to init sdl"<<std::endl;
        return EXIT_FAILURE;
    }
}
