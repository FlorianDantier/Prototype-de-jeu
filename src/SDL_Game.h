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
    void limitFPS(unsigned int limite);


private:
    // Méthodes privées
    void loadAllImage();
    void clean();

    // Membre SDL
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;
    Game g;
    unsigned int frameLimit;

    // Florian
    Image* m_mainBackground;
    Image* m_mainHomeBtn;

    Image* m_imageMap[2];


    // Franklin


    // Joris
    Image* m_warrior[4];
    Image* m_object[3];
    Image* m_enemyMap1[4];

};



#endif // SDL_GAME_H
