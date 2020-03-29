#include "Menu.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Character.h"
#include <vector>

const std::string path = "/home/joris/Bureau/lifap4/projet_lifap4/data/";



int main()
{


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;
    Rectangle posWar(50,300,50,50);
    Rectangle posEnemy(200,300,50,50);
    Rectangle origin(0,0,640,480);
    Character warrior(posWar,150,path+"Character.png",renderer,10);
    Character enemy(posEnemy,100,path+"Enemy.png",renderer,10);
    Image background(path+"background.png",origin,Vec2<unsigned int>(640,480),renderer);
    Character tabCharacter[1];
    tabCharacter[0]=enemy;
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
            warrior.event(event,tabCharacter);
        }

        SDL_RenderClear(renderer);
        // Tous les display ici
        background.display(renderer);
        SDL_Rect range = warrior.getRange().rectangle;
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            SDL_RenderFillRect(renderer,&range);
        }
        if(warrior.isAlive())
        {
            warrior.display(renderer);
        }
        for(unsigned int i = 0;i<1;i++)
        {
            if(tabCharacter[i].isAlive())
            {
                tabCharacter[i].display(renderer);
            }
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
