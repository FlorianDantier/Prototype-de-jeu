#include "SDL_Game.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "common.h"

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
    for(int i = 0; i < 4; i++)
    {
        delete m_warrior[i];
        m_warrior[i] = nullptr;
    }
    for(int i = 0; i < 3; i++)
    {
        delete m_object[i];
        m_object[i] = nullptr;
    }
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
    m_mainHomeBtn = new Image("../data/button.png", &g.getHome().getChoice(0).getPosition(), windowSize, m_pRenderer);
    static Rectangle r(0, 0, windowSize.x, windowSize.y);
    m_mainBackground = new Image("../data/background.png", &r, windowSize, m_pRenderer);
    m_warrior[Orientation::south] = new Image("../data/player/link.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_warrior[Orientation::north] = new Image("../data/player/linkDos.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_warrior[Orientation::east] = new Image("../data/player/linkDroit.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_warrior[Orientation::west] = new Image("../data/player/linkGauche.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_imageMap[map_1] = new Image("../data/map/map1.png", &r, windowSize ,m_pRenderer);
    m_imageMap[map_2] = new Image("../data/map/map2.png", &r, windowSize ,m_pRenderer);
    m_object[0] = new Image("../data/healthpotion.png",&g.getObject(0,map_1).getPos(),windowSize,m_pRenderer);
    m_object[1] = new Image("../data/hell's sword.png",&g.getObject(1,map_1).getPos(),windowSize,m_pRenderer);
    m_object[2] = new Image("../data/hell's armor.png",&g.getObject(2,map_1).getPos(),windowSize,m_pRenderer);
    //m_slime = new Image(path + "slime.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_enemyMap1[0] = new Image("../data/knight.png",&g.getEnemy(0,map_1).getPos(),windowSize,m_pRenderer);
    m_enemyMap1[1] = new Image("../data/knight.png",&g.getEnemy(1,map_1).getPos(),windowSize,m_pRenderer);
    m_enemyMap1[2] = new Image("../data/knight.png",&g.getEnemy(2,map_1).getPos(),windowSize,m_pRenderer);
    m_enemyMap1[3] = new Image("../data/knight.png",&g.getEnemy(3,map_1).getPos(),windowSize,m_pRenderer);
}

void SDL_Game::render()
{
    SDL_RenderClear(m_pRenderer);

    // Ici tous les affichage des images

    if(g.getStatus() == GameStatus::home)
    {
        m_mainBackground->display(m_pRenderer);
        m_mainHomeBtn->display(m_pRenderer);
    }
    else if(g.getStatus() == GameStatus::run)
    {
        m_imageMap[g.getMapLoad()]->display(m_pRenderer);
        if (g.getPlayer().isAlive())
        {
            m_warrior[g.getPlayer().getOrientation()]->display(m_pRenderer);
        }
        if (g.getMapLoad()==map_1)
        {
            for(int i = 0; i < 3; i++)
            {
                if(!g.getObject(i,map_1).isLooted())
                {
                    m_object[i]->display(m_pRenderer);
                }
            }

            for(int i = 0; i < 4; i++)
            {
                if(g.getEnemy(i,map_1).isAlive())
                {
                    m_enemyMap1[i]->display(m_pRenderer);
                }
            }
        }
    }
    else if(g.getStatus() == GameStatus::standBy)
    {

    }


    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
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
                if(g.getPlayer().isAlive())
                {

                    case SDLK_z:
                        g.touchZ(g.getMapLoad());
                        break;

                    case SDLK_q:
                        g.touchQ(g.getMapLoad());
                        break;

                    case SDLK_s:
                        g.touchS(g.getMapLoad());
                        break;

                    case SDLK_d:
                        g.touchD(g.getMapLoad());
                        break;

                    case SDLK_SPACE:
                        g.touchSpace(g.getMapLoad());
                        break;

                    case SDLK_c:
                        g.touchC();
                        break;

                    /*case SDLK_f:
                        g.touchF(g.getMapLoad());
                        break;*/
                }
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
    //=======ici les monstres bougent et tapent : IA========
    switch(g.getMapLoad())
    {
    case 0:
        for (int i=0;i<4;i++)
        {
            g.getEnemy(i,map_1).enemyPattern(g.getPlayer());
        }
        break;

    case 1:

        break;

    default:
        break;
    }
    //=====Fin IA=====
    //=========Le joueur lvl up=========
    if(g.getPlayer().getXpCurrent()>=g.getPlayer().getXpMax())
            {
                g.getPlayer().levelup();
            }
    //=====Fin lvl up=====
    SDL_Delay(100);
}

bool SDL_Game::getRunning()
{
    return m_bRunning;
}


