#include "Menu.h"
#include <SDL2/SDL.h>
#include <iostream>

const std::string path = "/home/florian/Dropbox/Licence/L2/S4/LIFAP4/projet_lifap4/data/";


class TestButton{
public:
    void (TestButton::*slot)();
    TestButton(){
        slot = &TestButton::buttonClicked;
    }
    void buttonClicked(){
        std::cout<<"Le bouton a été cliqué ..."<<std::endl;
    }
};



class A{
public:
    void doSomething(){
        std::cout<<"doing someething"<<std::endl;
    }
};


int main()
{
    Menu m;

    void (A::*ptr)();
    ptr = &A::doSomething;

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;
    Button b(Rectangle(0, 0, 100, 20), path + "button.png", renderer);
    bool run = true;
    while (run)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_QUIT:
                run = false;
                break;



              default:
                break;
            }
        }
        SDL_RenderClear(renderer);

        b.display(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
