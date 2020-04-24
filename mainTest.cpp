#include <iostream>


enum Test{
    droite = 0,
    gauche,
    bas,
    haut
};


int main (void)
{
  Test t = Test::droite;
  int tab[10] = {0};
    std::cout<<tab[t];
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
