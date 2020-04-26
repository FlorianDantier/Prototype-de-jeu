#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "common.h"
#include "Player.h"
#include "Enemy.h"

#include "Map.h"

namespace direction
{
    enum Type
    {
        top = 0,
        left,
        bottom,
        right
    };
}


class Game
{
private:
    // Florian
    Menu* m_home;
    Map* map1;
    GameStatus m_status;


    // Franklin



    // Joris
    Player * m_warrior;



public:
    Game();
    ~Game();

    // Florian
    Menu& getHome() const;
    void(Game::*ptrOnLauchGame)(GameStatus);
    GameStatus getStatus() const;
    void setStatus(const GameStatus gs);
    void controlePos();
    Map &getMap1() const;
    void eventManagers();
    bool collisionManager(const direction::Type d);
    void launchGame(const GameStatus gs);
    // Franklin



    // Joris
    Player& getPlayer() const;


    // Pour les touches ou click
    void touchZ();
    void touchQ();
    void touchS();
    void touchD();
    void mouseLeftClick(const Vec2<int> &mousePos);
};

#endif // GAME_H
