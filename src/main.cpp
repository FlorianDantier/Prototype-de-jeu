#include "Menu.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Character.h"

const std::string path = "/home/joris/Bureau/lifap4/projet_lifap4/data/";



int main()
{


    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_Event event;
    Rectangle posWar(0,0,50,50);
    Rectangle posEnemy(200,300,50,50);
    Rectangle origin(0,0,640,480);
    Character warrior(posWar,150,path+"Character.png",renderer,10);
    Character enemy(posEnemy,100,path+"Enemy.png",renderer,10);
    Image background(path+"background.png",origin,Vec2<unsigned int>(640,480),renderer);
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

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_z)
                {
                    std::cout<<"touche z appuyée : le joueur monte"<<std::endl;
                    warrior.event(event);
                    if(warrior.getPos().in(enemy.getPos()))
                    {
                        enemy.dealDamage(warrior);
                        std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                        std::cout<<"Vie de warrior restante : "<<warrior.getHealth()<<" HP"<<std::endl;
                        warrior.knockBack(event);
                    }
                }
                if (event.key.keysym.sym == SDLK_s)
                {
                    std::cout<<"touche s appuyée : le joueur descend"<<std::endl;
                    warrior.event(event);
                    if(warrior.getPos().in(enemy.getPos()))
                    {
                        enemy.dealDamage(warrior);
                        std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                        std::cout<<"Vie de warrior restante : "<<warrior.getHealth()<<" HP"<<std::endl;
                        warrior.knockBack(event);
                    }
                }
                if (event.key.keysym.sym == SDLK_q)
                {
                    std::cout<<"touche q appuyée : le joueur bouge a gauche"<<std::endl;
                    warrior.event(event);
                    if(warrior.getPos().in(enemy.getPos()))
                    {
                        enemy.dealDamage(warrior);
                        std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                        std::cout<<"Vie de warrior restante : "<<warrior.getHealth()<<" HP"<<std::endl;
                        warrior.knockBack(event);
                    }
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    std::cout<<"touche d appuyée : le joueur bouge a droite"<<std::endl;
                    warrior.event(event);
                    if(warrior.getPos().in(enemy.getPos()))
                    {
                        enemy.dealDamage(warrior);
                        std::cout<<"warrior touche ! il perd de la vie ..."<<std::endl;
                        std::cout<<"Vie de warrior restante : "<<warrior.getHealth()<<" HP"<<std::endl;
                        warrior.knockBack(event);

                    }

                }
                break;



              default:
                break;
            }
        }

        SDL_RenderClear(renderer);
        // Tous les display ici
        background.display(renderer);
        if(warrior.isAlive())
        {
            warrior.display(renderer);
        }
        if(enemy.isAlive())
        {
            enemy.display(renderer);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
