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
    // Méthodes privées
    void loadAllImage();
    void clean();

    // Membre SDL
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;
    Game g;

    // Florian
    Image* m_mainBackground;
    Image* m_mainHomeBtn;

    Image* m_imageMap[2];


    // Franklin


    // Joris
    Image* m_warrior[4];
    Image* m_object[3];

};

SDL_Rect SdlRect(const Rectangle & r)
{
    SDL_Rect r2 = {r.m_position.x, r.m_position.y, r.m_dimension.x, r.m_dimension.y};
    return r2;
}

#endif // SDL_GAME_H
