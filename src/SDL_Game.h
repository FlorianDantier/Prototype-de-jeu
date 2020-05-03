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


/**
 * @brief      This class describes a sdl game.
 */
class SDL_Game
{
public:
    /**
     * @brief      Constructs a new instance of SDL_Game
     */
    SDL_Game();

    /**
     * @brief      Destroys the object
     */
    ~SDL_Game();

    /**
     * @brief      Init the SDL library
     *
     * @param[in]  title   The window title
     * @param[in]  xPos    The x-coordinate of the window
     * @param[in]  yPos    The y-coordinate of the window
     * @param[in]  width   The window width
     * @param[in]  height  The window height
     *
     * @return     false if it failed, otherwise it returns true
     */
    bool init(std::string title, unsigned int xPos, unsigned int yPos,
              unsigned int width, unsigned int height);

    /**
     * @brief      render on the screen
     */
    void render();

    /**
     * @brief      true if the game is running
     *
     * @return     The running.
     */
    bool getRunning();

    /**
     * @brief      handle the events
     */
    void handleEvents();


private:
    /**
     * @brief      gives a limit to the number of frames per second
     *
     * @param[in]  limite  The fps limit
     */
    void limitFPS(unsigned int limite);

    /**
     * @brief      Loads all images
     */
    void loadAllImage();

    /**
     * @brief      clean the resources
     */
    void clean();

    /**
     * @brief      Loads all sounds
     */
    void loadAllSounds();

    /**
     * @brief      Loads all musics.
     */
    void loadAllMusics();


    /**
     * @brief      displays all enemies and objects
     */
    void renderEnnemysAndObjects();

    /**
     * @brief      displays the map
     */
    void renderMap();

    /**
     * @brief      displays the player inventory
     */
    void renderInventory();

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
    Mix_Chunk *m_MonsterDeathSound;

    // Florian
    Image* m_mainBackground;
    Image* m_mainHomeBtn;
    Image* m_imageMap[3];
    Image* m_imInventory;
    Image* m_closeInv;
    Image* m_openInv;
    Image* m_healButton;

    // Franklin


    // Joris
    Image* m_warrior[4];
    Image* m_sword[4];
    Image* m_objectMap1[3];
    Image* m_enemyMap1[4];
    Image* m_objectMap2[2];
    Image* m_enemyMap2[4];
    Image* m_enemyInstance[4];
    bool m_PlayerIsAttacking;
    time_t m_timerAnimSword;

};



#endif // SDL_GAME_H
