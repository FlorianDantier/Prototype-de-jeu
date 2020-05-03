#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "common.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"


/**
 * @brief      The direction of the player 
 */
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

/**
 * @brief      The map where the player is
 */
enum MapLoad
{
    map_1 = 0,
    map_2,
    instance1,
};

/**
 * @brief      This class describes a game.
 */
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
    /**
     * @brief      Constructs a new instance of Game
     */
    Game();
    /**
     * @brief      Destroys the object.
     */
    ~Game();

    // Florian
    

    /**
     * @brief      Gets the home as the menu
     *
     * @return     a reference to the menu
     */
    Menu& getHome() const;

    /**
     * @brief pointer to the ptrOnLaunchGame function
     * 
     */
    void(Game::*ptrOnLauchGame)(GameStatus);

    /**
     * @brief      Gets the status.
     *
     * @return     GameStatus
     */
    GameStatus getStatus() const;

    /**
     * @brief      Sets the status.
     *
     * @param[in]  gs    The new value
     */
    void setStatus(const GameStatus gs);

    /**
     * @brief      controlePos
     */
    void controlePos();

    /**
     * @brief      Gets the map 1.
     *
     * @param[in]  indice  The indice
     *
     * @return     The map 1.
     */
    Map &getMap1(unsigned int indice) const;

    /**
     * @brief      Manage key events
     *
     * @param[in]  touch  The character on the key pressed, for example 'Z', 'S', etc...
     */
    void eventManagers(const char touch);

    /**
     * @brief      Manage the collision
     *
     * @param      pos      The position
     * @param[in]  tabPos   The array that contains positions
     * @param[in]  sizeTab  The size of the array tabPos
     * @param[in]  d        direction
     *
     * @return     { description_of_the_return_value }
     */
    bool collisionManager(Rectangle &pos, const Rectangle *tabPos,
                          const unsigned int sizeTab, const direction::Type d);

    /**
     * @brief      launch the game
     *
     * @param[in]  gs    status of the game
     */
    void launchGame(const GameStatus gs);

    /**
     * @brief      Determines whether the specified rectangle is at the edge.
     *
     * @param[in]  rect  The rectangle
     *
     * @return     The direction type.
     */
    direction::Type isAtTheEdge(const Rectangle & rect);

    /**
     * @brief      Manage the change of map
     */
    void changeMapManager();

    /**
     * @brief      Sets the map load.
     *
     * @param[in]  m     The new value
     */
    void setMapLoad(const MapLoad m);

    /**
     * @brief      Gets the map load.
     *
     * @return     The map load.
     */
    MapLoad getMapLoad() const;

    /**
     * @brief      Loads a new zone.
     */
    void loadNewZone();

    /**
     * @brief   call touchX where X is the key pressed
     *
     * @param[in]  touch  the character corresponding to the key pressed
     */
    void eventTouch(const char touch);

    /**
     * @brief      Manage enemies
     */
    void ennemyManager();

    /**
     * @brief      Gets the number of map.
     *
     * @return     The number of map.
     */
    unsigned int getNbMap() const;

    /**
     * @brief      Gets the inventory, a menu
     *
     * @return     The inventory.
     */
    Menu &getInventory() const;

    /**
     * @brief      heal
     */
    void heal();

    /**
     * function pointer to OnHeal procedure
     */
    void(Game::*ptrOnHeal)();
    // Franklin



    // Joris

    /**
     * @brief      Gets the player.
     *
     * @return     A reference to the player.
     */
    Player& getPlayer() const;

    /**
     * @brief      Gets the object.
     *
     * @param[in]  indice  The index
     * @param[in]  ml      The map
     *
     * @return     The object.
     */
    Object& getObject(unsigned int indice, MapLoad ml) const;

    /**
     * @brief      Gets the enemy.
     *
     * @param[in]  indice  The index
     * @param[in]  ml      The map
     *
     * @return     The enemy.
     */
    Enemy& getEnemy(unsigned int indice, MapLoad ml) const;

    /**
     * @brief      Gets all enemy position.
     *
     * @param[in]  tabEnemy  The array of enemies
     * @param[in]  sizeTab   The size of the array
     *
     * @return     All enemy position.
     */
    Rectangle& getAllEnemyPos(const Enemy *tabEnemy,unsigned int sizeTab);
    //retourne un tableau avec toutes les positions des ennemis

    /**
     * @brief      Gets all the enemies
     *
     * @param[in]  ml    The map
     *
     * @return     one dimension array of Enemy
     */
    Enemy* getAllEnemy(MapLoad ml) const;
    //retourne le tableau des ennemis

    // Pour les touches ou click

    /**
     * @brief      move the player up
     */
    void touchZ();

    /**
     * @brief      move the player to the left
     */
    void touchQ();

    /**
     * @brief      move the player down
     */
    void touchS();

    /**
     * @brief      move the player to the right
     */
    void touchD();

    /**
     * @brief      the player picks up the nearest object
     */
    void touchF();

    /**
     * @brief      print in the console terminal the player statistics
     */
    void touchC();

    /**
     * @brief      sword attack
     */
    void touchSpace();

    /**
     * @brief      if the player left-clicks
     *
     * @param[in]  mousePos  The mouse position
     */
    void mouseLeftClick(const Vec2<int> &mousePos);
};

#endif // GAME_H
