#ifndef SDL_GAME_H
#define SDL_GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Game.h"
#include "Image.h"
#include <string>

enum Music
{
    cool,
    techno,
};

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
    void loadAllSounds();
    void loadAllMusics();

    // Membre SDL
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;
    Game g;
    unsigned int frameLimit;
    Music m_whichMusic;
    Mix_Music *m_cool_music;
    Mix_Music *m_techno_music;
    Mix_Chunk *m_attackSound;
    Mix_Chunk *m_levelupSound;
    Mix_Chunk *m_menuClicSound;

    // Florian
    Image* m_mainBackground;
    Image* m_mainHomeBtn;

    Image* m_imageMap[3];


    // Franklin


    // Joris
    Image* m_warrior[4];
    Image* m_sword[4];
    Image* m_objectMap1[3];
    Image* m_enemyMap1[4];
    Image* m_objectMap2[2];
    Image* m_enemyMap2[4];
    Image* m_enemyInstance[4];

};



#endif // SDL_GAME_H
