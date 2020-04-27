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
        right,
        noValue,
    };
}

enum MapLoad
{
    map_1 = 0,
    map_2,
};


class Game
{
private:
    // Florian
    Menu* m_home;
    Map* map[2];
    unsigned int nbMap;
    GameStatus m_status;
    MapLoad ml;

    // Franklin



    // Joris
    Player * m_warrior;
    //Enemy * m_tabEnemyMap1[4];
    Object * m_tabObjectMap1[3];


public:
    Game();
    ~Game();

    // Florian
    Menu& getHome() const;
    void(Game::*ptrOnLauchGame)(GameStatus);
    GameStatus getStatus() const;
    void setStatus(const GameStatus gs);
    void controlePos();
    Map &getMap1(unsigned int indice) const;
    void eventManagers();
    bool collisionManager(const direction::Type d);
    void launchGame(const GameStatus gs);
    direction::Type isAtTheEdge(const Rectangle & rect);
    void changeMapManager();
    void setMapLoad(const MapLoad m);
    MapLoad getMapLoad() const;

    // Franklin



    // Joris
    Player& getPlayer() const;
    Object& getObject(unsigned int indice) const;

    // Pour les touches ou click
    void touchZ();
    void touchQ();
    void touchS();
    void touchD();
    void touchF();
    void mouseLeftClick(const Vec2<int> &mousePos);
};

#endif // GAME_H
