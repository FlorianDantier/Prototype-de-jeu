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
    instance1,
};


class Game
{
private:
    // Florian
    Menu* m_home;
    Map* m_map[2];
    unsigned int m_nbMap;
    GameStatus m_status;
    MapLoad m_ml;

    // Franklin



    // Joris
    Player * m_warrior;
    Enemy * m_tabEnemyMap1[4];
    Enemy * m_tabEnemyMap2[4];
    Object * m_tabObjectMap1[3];
    Object * m_tabObjectMap2[2];


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
    bool collisionManager(Rectangle &pos, const Rectangle *tabPos, const unsigned int sizeTab, const direction::Type d);
    void launchGame(const GameStatus gs);
    direction::Type isAtTheEdge(const Rectangle & rect);
    void changeMapManager();
    void setMapLoad(const MapLoad m);
    MapLoad getMapLoad() const;
    void loadNewZone();

    // Franklin



    // Joris
    Player& getPlayer() const;
    Object& getObject(unsigned int indice, MapLoad ml) const;
    Enemy& getEnemy(unsigned int indice,MapLoad ml) const;

    // Pour les touches ou click
    void touchZ(MapLoad ml);
    void touchQ(MapLoad ml);
    void touchS(MapLoad ml);
    void touchD(MapLoad ml);
    void touchF(MapLoad ml);
    void touchC();
    void touchSpace(MapLoad ml);
    void mouseLeftClick(const Vec2<int> &mousePos);
};

#endif // GAME_H
