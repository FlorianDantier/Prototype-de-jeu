#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "common.h"




class Game
{
private:
    // Florian
    Menu* m_home;
    GameStatus m_status;


    // Franklin



    // Joris




public:
    Game();
    ~Game();

    // Florian
    Menu& getHome() const;
    void setStatus(bool b);
    void(Game::*ptrONsetStatus)(GameStatus);
    GameStatus getStatus() const;
    void setStatus(const GameStatus gs);

    void eventManagers();

    // Franklin



    // Joris



    // Pour les touches ou click
    void touchZ();
    void touchQ();
    void touchS();
    void touchD();
    void mouseLeftClick(const Vec2<int> &mousePos);
};

#endif // GAME_H
