#include "SDL_Game.h"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Game::SDL_Game() : m_mainHomeBtn(nullptr), m_mainBackground(nullptr)
{
    m_pWindow = NULL;
    m_pRenderer = NULL;
    m_bRunning = true;
}

SDL_Game::~SDL_Game()
{
    clean();
    delete m_mainHomeBtn;
    delete m_mainBackground;
}

bool SDL_Game::init(std::string title, unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"SDL init success\n";
        m_pWindow = SDL_CreateWindow(title.c_str(), xPos, yPos, width, height, SDL_WINDOW_SHOWN);

        if(m_pWindow != NULL)
        {
            std::cout << "window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            if(m_pRenderer != NULL)
            {
                std::cout << "renderer creation success\n";
            }
            else
            {
               std::cout << "renderer init fail\n";
               return false;
            }
        }
        else
        {
            std::cout << "window init fail\n";
            return false;
        }

    }
    else
    {
        std::cout << "SDL init fail\n";
        return false;
    }

    std::cout << "init success\n";
    m_bRunning = true;
    // Si tout est ok on charge les images....
    loadAllImage();
    return true;

}

/* ===============================!!!!!!!!!!!IMPORTANT!!!!!!!!!!!==================================*/
// Postion de l'image à initialiser avec l'adresse du rectangle representant la position de l'objet
// Toutes les images seront chargé dynamiquement ci-dessous, donc n'oubliez pas le DELETE DANS LE DESTRUCTEUR.
void SDL_Game::loadAllImage()
{
    m_mainHomeBtn = new Image(path + "button.png", &g.getHome().getChoice(0).getPosition(), windowSize, m_pRenderer);
    static Rectangle r(0, 0, windowSize.x, windowSize.y);
    m_mainBackground = new Image(path + "background.png", &r, windowSize, m_pRenderer);
}

void SDL_Game::render()
{
    SDL_RenderClear(m_pRenderer);

    // Ici tous les affichage des images
    /* ==========Florian============ */
    m_mainBackground->display(m_pRenderer);
    m_mainHomeBtn->display(m_pRenderer);



    /*=============Joris===============*/




    /* ===========Franklin========== */




    //==========FIN AFFICHAGE=========
    SDL_RenderPresent(m_pRenderer);
}

void SDL_Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
    std::cout<<"called clean"<<std::endl;
}

void SDL_Game::handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {

        switch(event.type)
        {
            case SDL_QUIT:
                m_bRunning = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {

                    case SDLK_z:
                        g.touchZ();
                        break;

                    case SDLK_q:
                        g.touchQ();
                        break;

                    case SDLK_s:
                        g.touchS();
                        break;

                    case SDLK_d:
                        g.touchD();
                        break;

                        // Ne pas hésitez à rajouter des touches au besoin...
                        // Si rajout de touche, bien crée la fonction touch dans Game

                    case SDLK_ESCAPE:
                        m_bRunning = false;
                        break;

                    default:
                        break;

                }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT) // Click gauche
            {
                 g.mouseLeftClick(Vec2<int>(event.button.x, event.button.y));
            }
            else if(event.button.button == SDL_BUTTON_RIGHT)
            {
                // Tous les actions devant s'éxecuter lors d'un click droit à mettre en dessous
            }

            break;

        default:
            break;
        }
    }
}

bool SDL_Game::getRunning()
{
    return m_bRunning;
}


