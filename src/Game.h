#ifndef GAME_H
#define GAME_H

#include "Menu.h"

const Vec2<unsigned int> windowSize(640, 480);

class Game
{
private:
    // Florian
    Menu* m_home;


    // Franklin



    // Joris



    bool m_isRunning; // Jeu en pause ou pas
public:
    Game();
    ~Game();

    // Florian
    Menu& getHome() const;


    // Franklin



    // Joris


};

#endif // GAME_H
