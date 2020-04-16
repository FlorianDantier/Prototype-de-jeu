#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include "Game.h"
#include "Image.h"
#include <string>


class SDL_Game
{
public:
    SDL_Game();
    ~SDL_Game();

    bool init(std::string title, unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height);

    void render();
    void handleEvents();

    bool getRunning();


private:
    // Méthode privées
    void loadAllImage();
    void clean();

    void touchZ();
    void touchQ();
    void touchS();
    void touchD();
    // Membre SDL
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;
    Game g;

    // Florian
    Image* m_menuImage;


    // Franklin


    // Joris


};

#endif // SDL_GAME_H
