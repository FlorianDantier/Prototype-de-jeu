#include <iostream>
//#include <SDL2/SDL.h>
//#include "Rectangle.h"
//#include "Button.h"
//#include "Menu.h"
//#include "Image.h"

//const std::string path = "/home/florian/Cours/LIFAP4/projet_lifap4/data/";

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
//    SDL_Init(SDL_INIT_EVERYTHING);
//    SDL_Window* window = SDL_CreateWindow("Brain Dead", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
//    SDL_Event event;
//    Rectangle perso(20, 20, 100, 100);
//    Image im(path + "button.png", &perso, Vec2<unsigned int>(640, 480), renderer);
//    bool run = true;
//    while (run)
//    {
//        while(SDL_PollEvent(&event))
//        {
//            switch (event.type)
//            {
//                case SDL_QUIT:
//                run = false;
//                    break;
//            case SDL_KEYDOWN:
//                switch (event.key.keysym.sym)
//                {
//                    case SDLK_z:
//                    perso.m_position.y --;
//                    break;

//                    case SDLK_s:
//                    perso.m_position.y++;
//                    break;

//                    case SDLK_q:
//                    perso.m_position.x--;
//                    break;

//                    case SDLK_d:
//                    perso.m_position.x++;
//                    break;
//                }

//                break;

//            default:
//                break;
//            }
//        }
//        SDL_RenderClear(renderer);
//        im.display(renderer);
//        SDL_RenderPresent(renderer);
//    }

//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
}
