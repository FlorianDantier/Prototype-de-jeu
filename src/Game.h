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
    Map* m_map[3];
    unsigned int m_nbMap;
    GameStatus m_status;
    MapLoad m_ml;
    Menu* m_inventory;

    // Franklin



    // Joris
    Player * m_warrior;
    Enemy * m_tabEnemyMap1[4];
    Enemy * m_tabEnemyMap2[4];
    Object * m_tabObjectMap1[3];
    Object * m_tabObjectMap2[2];
    Enemy * m_tabEnemyInstance[4];
    Rectangle * m_tabPosEnemy;


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
    void eventManagers(const char touch);
    bool collisionManager(Rectangle &pos, const Rectangle *tabPos,
                          const unsigned int sizeTab, const direction::Type d);
    void launchGame(const GameStatus gs);
    direction::Type isAtTheEdge(const Rectangle & rect);
    void changeMapManager();
    void setMapLoad(const MapLoad m);
    MapLoad getMapLoad() const;
    void loadNewZone();
    void eventTouch(const char touch);
    void ennemyManager();
    unsigned int getNbMap() const;
    Menu &getInventory() const;

    void heal();
    void(Game::*ptrOnHeal)();
    // Franklin



    // Joris
    Player& getPlayer() const;
    Object& getObject(unsigned int indice, MapLoad ml) const;
    Enemy& getEnemy(unsigned int indice,MapLoad ml) const;
    Rectangle& getAllEnemyPos(const Enemy *tabEnemy,unsigned int sizeTab);
    //retourne un tableau avec toutes les positions des ennemis
    Enemy* getAllEnemy(MapLoad ml) const;
    //retourne le tableau des ennemis

    // Pour les touches ou click
    void touchZ();
    void touchQ();
    void touchS();
    void touchD();
    void touchF();
    void touchC();
    void touchSpace();
    void mouseLeftClick(const Vec2<int> &mousePos);
};

#endif // GAME_H
