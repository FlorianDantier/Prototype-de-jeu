#include "Menu.h"
#include <SDL2/SDL.h>
#include <iostream>

const std::string path = "/home/florian/Dropbox/Licence/L2/S4/LIFAP4/projet_lifap4/data/";

// Tester close Button et open Button
class TestButton{
private:
    int m_i;
public:
    void (TestButton::*slot)();
    void (TestButton::*spmt)(int);
    TestButton(){
        m_i = 0;
        slot = &TestButton::buttonClicked;
        spmt = &TestButton::afficheeppi;
    }
    void buttonClicked(){
        std::cout<<"Le bouton a été cliqué ..."<<std::endl;
    }

    void afficheeppi(int i)
    {
        i++;
        std::cout<<i<<std::endl;
    }
};


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;


    Rectangle r1(0, 0, 100, 40);
    Rectangle r2(100, 200, 100, 130);



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

            case SDL_KEYDOWN :
                switch (event.key.keysym.sym) {
                case SDLK_z:
                    r1.rectangle.y --;
                    break;
                case SDLK_s:
                    r1.rectangle.y++;
                    break;
                case SDLK_q:
                    r1.rectangle.x--;
                    break;
                case SDLK_d:
                    r1.rectangle.x++;
                    break;

                case SDLK_p:
                    std::cout<<"===================================================================="<<std::endl;
                }



              default:
                break;
            }

        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &r1.rectangle);
        if(r1.in(r2)) std::cout<<"Colision\n";
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 100);
        SDL_RenderFillRect(renderer, &r2.rectangle);


        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
