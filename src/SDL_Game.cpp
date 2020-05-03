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
        delete m_objectMap1[i];
        m_objectMap1[i] = nullptr;
    }
    for(int i = 0; i < 2; i++)
    {
        delete m_objectMap2[i];
        m_objectMap2[i] = nullptr;
    }
    for(int i = 0; i < 4; i++)
    {
        delete m_enemyMap1[i];
        m_enemyMap1[i] = nullptr;
    }
    for(int i = 0; i < 4; i++)
    {
        delete m_enemyMap2[i];
        m_enemyMap2[i] = nullptr;
    }
    for(int i = 0; i < 4; i++)
    {
        delete m_enemyInstance[i];
        m_enemyInstance[i] = nullptr;
    }
    for(int i = 0; i < 4; i++)
    {
        delete m_sword[i];
        m_sword[i] = nullptr;
    }
    for(unsigned int i = 0; i < g.getNbMap(); i++)
    {
        delete m_imageMap[i];
        m_imageMap[i] = nullptr;
    }
    delete m_closeInv;
    m_closeInv = nullptr;

    delete m_imInventory;
    m_imInventory = nullptr;

    delete m_openInv;
    m_openInv = nullptr;

    delete m_healButton;
    m_healButton = nullptr;

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
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
                                   {
                                      printf("%s", Mix_GetError());
                                   }
                                else
                                {
                                    std::cout<<"SDL Mixer opened"<<std::endl;
                                    m_whichMusic = cool;
                                    Mix_AllocateChannels(3);// création canneaux pour les sons
                                    std::cout<<"Channels creation success"<<std::endl;

                                }
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
    loadAllSounds();
    loadAllMusics();
    frameLimit = SDL_GetTicks() + 16;
    Mix_PlayMusic(m_cool_music, -1);
    Mix_PauseMusic();
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
    //=========Image joueur warrior=========
    m_warrior[Orientation::south] = new Image("../data/player/link.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_warrior[Orientation::north] = new Image("../data/player/linkDos.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_warrior[Orientation::east] = new Image("../data/player/linkDroit.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    m_warrior[Orientation::west] = new Image("../data/player/linkGauche.png",&g.getPlayer().getPos(),windowSize,m_pRenderer);
    //=========Fin image warrior============
    //=========Image épée===========
    m_sword[Orientation::south] = new Image("../data/sword/swordBottom.png",&g.getPlayer().getRange(),windowSize,m_pRenderer);
    m_sword[Orientation::north] = new Image("../data/sword/swordTop.png",&g.getPlayer().getRange(),windowSize,m_pRenderer);
    m_sword[Orientation::east] = new Image("../data/sword/swordRight.png",&g.getPlayer().getRange(),windowSize,m_pRenderer);
    m_sword[Orientation::west] = new Image("../data/sword/swordLeft.png",&g.getPlayer().getRange(),windowSize,m_pRenderer);
    //=========Fin image épée=======
    m_imageMap[map_1] = new Image("../data/map/map1.png", &r, windowSize ,m_pRenderer);
    m_imageMap[map_2] = new Image("../data/map/map2.png", &r, windowSize ,m_pRenderer);
    m_imageMap[instance1] = new Image("../data/map/instance.png", &r, windowSize, m_pRenderer);
    //=========Image pour map1==========
    //pour object map1
    m_objectMap1[0] = new Image("../data/healthpotion.png",&g.getObject(0,map_1).getPos(),windowSize,m_pRenderer);
    m_objectMap1[1] = new Image("../data/hell's sword.png",&g.getObject(1,map_1).getPos(),windowSize,m_pRenderer);
    m_objectMap1[2] = new Image("../data/hell's armor.png",&g.getObject(2,map_1).getPos(),windowSize,m_pRenderer);
    //pour enemy Map1
    m_enemyMap1[0] = new Image("../data/knight.png",&g.getEnemy(0,map_1).getPos(),windowSize,m_pRenderer);
    m_enemyMap1[1] = new Image("../data/knight.png",&g.getEnemy(1,map_1).getPos(),windowSize,m_pRenderer);
    m_enemyMap1[2] = new Image("../data/eliteKnight.png",&g.getEnemy(2,map_1).getPos(),windowSize,m_pRenderer);
    m_enemyMap1[3] = new Image("../data/knight.png",&g.getEnemy(3,map_1).getPos(),windowSize,m_pRenderer);
    //=========Fin Image map1=========

    //=========Image pour map2=========
    //pour object map2
    m_objectMap2[0] = new Image("../data/healthpotion.png",&g.getObject(0,map_2).getPos(),windowSize,m_pRenderer);
    m_objectMap2[1] = new Image("../data/healthpotion.png",&g.getObject(1,map_2).getPos(),windowSize,m_pRenderer);
    //pour enemy map2
    m_enemyMap2[0] = new Image("../data/eliteKnight.png",&g.getEnemy(0,map_2).getPos(),windowSize,m_pRenderer);
    m_enemyMap2[1] = new Image("../data/eliteKnight.png",&g.getEnemy(1,map_2).getPos(),windowSize,m_pRenderer);
    m_enemyMap2[2] = new Image("../data/skeletonJedi.png",&g.getEnemy(2,map_2).getPos(),windowSize,m_pRenderer);
    m_enemyMap2[3] = new Image("../data/knight.png",&g.getEnemy(3,map_2).getPos(),windowSize,m_pRenderer);
    //=========Fin Image map2=========

    //=========Image pour Instance1=======
    m_enemyInstance[0] = new Image("../data/dragon.png",&g.getEnemy(0,instance1).getPos(),windowSize,m_pRenderer);
    m_enemyInstance[1] = new Image("../data/cyclop.png",&g.getEnemy(1,instance1).getPos(),windowSize,m_pRenderer);
    m_enemyInstance[2] = new Image("../data/cyclop.png",&g.getEnemy(2,instance1).getPos(),windowSize,m_pRenderer);
    m_enemyInstance[3] = new Image("../data/cyclop.png",&g.getEnemy(3,instance1).getPos(),windowSize,m_pRenderer);
    //=========Fin image pour instance1===

    Rectangle r5(200, 200, 100, 100);
    m_imInventory = new Image("../data/inventaire.png", &g.getInventory().getPosition(), windowSize, m_pRenderer);
    m_openInv = new Image("../data/open.png", &g.getInventory().getOpenButton().getPosition(), windowSize, m_pRenderer);
    m_closeInv = new Image("../data/close.png", &g.getInventory().getCloseButton().getPosition(), windowSize, m_pRenderer);
    m_healButton = new Image("../data/healthpotion.png", &g.getInventory().getChoice(0).getPosition(), windowSize, m_pRenderer);

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
    else if(g.getStatus() == GameStatus::run || g.getStatus() == GameStatus::standBy)
    {
        m_imageMap[g.getMapLoad()]->display(m_pRenderer);
        if (g.getPlayer().isAlive())
        {
            m_warrior[g.getPlayer().getOrientation()]->display(m_pRenderer);
        }
       switch(g.getMapLoad())
        {
       case 0:
            for(int i = 0; i < 3; i++)
            {
                if(!g.getObject(i,map_1).isLooted())
                {
                    m_objectMap1[i]->display(m_pRenderer);
                }
            }

            for(int i = 0; i < 4; i++)
            {
                if(g.getEnemy(i,map_1).isAlive())
                {
                    m_enemyMap1[i]->display(m_pRenderer);
                }
            }
           break;

       case 1:
           for(int i = 0; i < 2; i++)
           {
               if(!g.getObject(i,map_2).isLooted())
               {
                   m_objectMap2[i]->display(m_pRenderer);
               }
           }

           for(int i = 0; i < 4; i++)
           {
               if(g.getEnemy(i,map_2).isAlive())
               {
                   m_enemyMap2[i]->display(m_pRenderer);
               }
           }
           break;
       case 2:
           for(int i = 0; i < 4; i++)
           {
               if(g.getEnemy(i,instance1).isAlive())
               {
                   m_enemyInstance[i]->display(m_pRenderer);
               }
           }

       default:
           break;

        }

       if(g.getInventory().getIsLoad())
       {
           if(g.getInventory().getIsOpen())
           {
               m_imInventory->display(m_pRenderer);
               m_closeInv->display(m_pRenderer);
               m_healButton->display(m_pRenderer);
               SDL_SetRenderDrawColor(m_pRenderer, 50, 200, 20, SDL_ALPHA_OPAQUE);
           }
           else
           {
               m_openInv->display(m_pRenderer);
           }
       }
    }
    else if(g.getStatus() == GameStatus::standBy)
    {

    }


    limitFPS(frameLimit);
    //==========FIN AFFICHAGE=========
    SDL_RenderPresent(m_pRenderer);
    frameLimit = SDL_GetTicks() + 16;
}

void SDL_Game::clean()
{
    std::cout << "cleaning game\n";
    Mix_FreeChunk(m_attackSound);
    Mix_FreeChunk(m_levelupSound);
    Mix_FreeChunk(m_menuClicSound);
    Mix_FreeMusic(m_cool_music);
    Mix_FreeMusic(m_techno_music);
    Mix_CloseAudio();// fermeture Api Mixer
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
    std::cout<<"called clean"<<std::endl;
}
void SDL_Game::loadAllSounds()
{
    m_attackSound = Mix_LoadWAV("../data/sound/swish.wav");
    m_levelupSound = Mix_LoadWAV("../data/sound/levelup.wav");
    m_menuClicSound = Mix_LoadWAV("../data/sound/menu_clic.wav");
}

void SDL_Game::loadAllMusics()
{
    m_cool_music = Mix_LoadMUS("../data/music/cool.mp3");
    m_techno_music = Mix_LoadMUS("../data/music/techno.mp3");
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
                        g.eventTouch('z');
                        break;

                    case SDLK_q:
                        g.eventTouch('q');
                        break;

                    case SDLK_s:
                        g.eventTouch('s');
                        break;

                    case SDLK_d:
                        g.eventTouch('d');
                        break;

                    case SDLK_SPACE:
                        m_sword[g.getPlayer().getOrientation()]->display(m_pRenderer);
                        g.eventTouch(' ');
                        Mix_PlayChannel(1,m_attackSound,0);
                        break;

                    case SDLK_c:
                        g.eventTouch('c');
                        break;

                    case SDLK_f:
                        g.eventTouch('f');
                        break;
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
                 Mix_PlayChannel(2,m_menuClicSound,0);
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
    //=======ici les musiques suivant la map=========
        if(g.getStatus() == GameStatus::run)
        {
            switch(g.getMapLoad())
            {
            case 0:
                if((Mix_PlayingMusic()==1)&& m_whichMusic==techno)
                {
                    Mix_HaltMusic();
                    Mix_RewindMusic();
                    Mix_PlayMusic(m_cool_music,-1);
                    m_whichMusic = cool;
                }
                else if((Mix_PausedMusic()==1)&& m_whichMusic==cool)
                {
                    Mix_ResumeMusic();
                }
                break;
            case 1:
                if((Mix_PlayingMusic()==1)&& m_whichMusic==techno)
                {
                    Mix_HaltMusic();
                    Mix_RewindMusic();
                    Mix_PlayMusic(m_cool_music,-1);
                    m_whichMusic = cool;
                }
                else if((Mix_PausedMusic()==1)&& m_whichMusic==cool)
                {
                    Mix_ResumeMusic();
                }
                break;
            case 2:
                if((Mix_PlayingMusic()==1)&& m_whichMusic==cool)
                {
                    Mix_HaltMusic();
                    Mix_RewindMusic();
                    Mix_PlayMusic(m_techno_music,-1);
                    m_whichMusic = techno;
                }
                break;
            default:
                break;
            }
        }

        //=======Fin musiques============================

    //=======ici les monstres bougent et tapent : IA========
    g.ennemyManager();
    //=====Fin IA=====
    //=========Le joueur lvl up=========
    if(g.getPlayer().getXpCurrent()>=g.getPlayer().getXpMax())
    {
        g.getPlayer().levelup();
        Mix_PlayChannel(2,m_levelupSound,0);
    }
    //=====Fin lvl up=====
}

bool SDL_Game::getRunning()
{
    return m_bRunning;
}

void SDL_Game::limitFPS(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
    {
        return;
    }
    else if(limit > ticks + 16)
    {
        SDL_Delay(16);
    }
    else
    {
        SDL_Delay(limit - ticks);
    }
}


