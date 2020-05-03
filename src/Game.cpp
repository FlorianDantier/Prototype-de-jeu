#include "Game.h"
#include <cassert>

Game::Game() : m_home(nullptr), m_status(GameStatus::home)
{
    m_nbMap = 3;
    for(unsigned int i = 0; i < m_nbMap; i++)
    {
        m_map[i] = nullptr;
    }
    ptrOnLauchGame = &Game::launchGame;
    ptrOnHeal = &Game::heal;
    Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
    m_home = new Menu(1, Rectangle(0, 0, windowSize.x, windowSize.y),
                      true, true, notLoad, notLoad);
    // Le menu "home" est une exception dans le sens où il n'y aura pas de bouton pour ouvir ou fermer ce menu
    m_home->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);

    m_ml = map_1;
    //=============== Création des maps==================
    m_map[map_1] = new Map(73, 2, map_1);
    assert(m_map[map_1] != nullptr);

    m_map[map_2] = new Map(104, 1, map_2);
    assert(m_map[map_2] != nullptr);

    m_map[instance1] = new Map(60, 2, instance1);
    assert(m_map[instance1] != nullptr);
    // =========Fin de création des maps================
    // =========Ajout du Player==========
    Rectangle warPos(windowSize.x / 2, windowSize.y / 2, 25, 34);
    m_warrior = new Player("Bob", warrior, warPos, 100, 1);

    // =========Fin ajout du Player==========

    // =========Ajout des Objets dans les maps=========
    //pour la map1
    m_tabObjectMap1[0] = new Object("Health Potion",other,500,
                                    Rectangle(217,663,20,20),50,false,true);
    m_tabObjectMap1[1] = new Object("Hell's Sword",weapon,500,
                                    Rectangle(600,574,20,20),50,false,true);
    m_tabObjectMap1[2] = new Object("Hell's Armor",armor,500,
                                    Rectangle(475,310,20,20),20,false,true);
    //Fin pour la map1

    //pour la map2
    m_tabObjectMap2[0] = new Object("Health Potion",other,500,
                                    Rectangle(570,50,20,20),50,false,true);
    m_tabObjectMap2[1] = new Object("Health Potion",other,500,
                                    Rectangle(700,650,20,20),50,false,true);
    //Fin pour la map2

    // =========Fin Ajout des objets dans les maps=========

    // =========Ajout des ennemis dans les maps=========
    //pour la map1
    m_tabEnemyMap1[0] = new Enemy(sbire,humanoid,Rectangle(350,5,25,50),
                                  150,1,horizontalLeft,false);
    m_tabEnemyMap1[1] = new Enemy(sbire,humanoid,Rectangle(550,150,25,50),
                                  150,1,horizontalRight,false);
    m_tabEnemyMap1[2] = new Enemy(elite,humanoid,Rectangle(180,350,32,64),
                                  500,1,verticalBottom,false);
    m_tabEnemyMap1[3] = new Enemy(sbire,humanoid,Rectangle(400,550,25,50),
                                  200,1,verticalTop,false);
    //Fin pour la map1

    //pour l'instance 1
    m_tabEnemyInstance[0] = new Enemy(boss,beast,Rectangle(340,120,100,150),
                                  3000,3,horizontalLeft,false);
    m_tabEnemyInstance[1] = new Enemy(elite,beast,Rectangle(140,370,40,80),
                                  500,3,verticalBottom,false);
    m_tabEnemyInstance[2] = new Enemy(elite,beast,Rectangle(375,475,40,80),
                                  500,3,verticalBottom,false);
    m_tabEnemyInstance[3] = new Enemy(elite,beast,Rectangle(630,350,40,80),
                                  500,3,verticalTop,false);
    //Fin pour l'instance 1


    //pour la map2
    m_tabEnemyMap2[0] = new Enemy(elite,humanoid,Rectangle(255,600,32,64),
                                  500,2,verticalTop,false);
    m_tabEnemyMap2[1] = new Enemy(elite,humanoid,Rectangle(550,370,32,64),
                                  500,2,horizontalRight,false);
    m_tabEnemyMap2[2] = new Enemy(boss,humanoid,Rectangle(500,600,50,100),
                                  2000,2,horizontalLeft,false);
    m_tabEnemyMap2[3] = new Enemy(sbire,humanoid,Rectangle(150,150,32,64),
                                  200,2,horizontalLeft,false);
    //Fin pour la map2

    // =========Fin Ajout des ennemis dans les maps=========

    // Inventaire (pseudo)
    Rectangle posInv(320, 185, 200, 275);
    Button close(Rectangle(320, 185, 25, 24), false);
    Button open(Rectangle(732, 755, 66, 45), false);
    m_inventory = new Menu(1, posInv, false, false, open, close);
    Button health(Rectangle(385, 300, 75, 71), false);
    m_inventory->setChoice(health, 0);
}

Game::~Game()
{
    delete m_home;
    m_home = nullptr;

    delete m_warrior;
    m_warrior = nullptr;

    for(unsigned int i = 0; i < m_nbMap; i++)
    {
        delete m_map[i];
        m_map[i] = nullptr;
    }
    for(unsigned int i = 0; i < 3; i++)
    {
        delete m_tabObjectMap1[i];
        m_tabObjectMap1[i] = nullptr;
    }
    for(unsigned int i = 0; i < 4; i++)
    {
        delete m_tabEnemyMap1[i];
        m_tabEnemyMap1[i] = nullptr;
    }
    for(unsigned int i = 0; i < 2; i++)
    {
        delete m_tabObjectMap2[i];
        m_tabObjectMap2[i] = nullptr;
    }
    for(unsigned int i = 0; i < 4; i++)
    {
        delete m_tabEnemyMap2[i];
        m_tabEnemyMap2[i] = nullptr;
    }
    for(unsigned int i = 0; i < 4; i++)
    {
        delete m_tabEnemyInstance[i];
        m_tabEnemyInstance[i] = nullptr;
    }

    delete m_inventory;
    m_inventory = nullptr;
}

Menu& Game::getHome() const
{
    return *m_home;
}

GameStatus Game::getStatus() const
{
    return m_status;
}

void Game::setStatus(const GameStatus gs)
{
  m_status = gs;
}

void Game::launchGame(const GameStatus gs)
{
    std::cout<<"marche"<<std::endl;
    setStatus(gs);
    m_home->getChoice(0).setIsLoad(false);
    m_inventory->setIsLoad(true);
}

direction::Type Game::isAtTheEdge(const Rectangle &rect)
{
    if(rect.m_position.x <= -15)
    {
        return direction::left;
    }
    else if(rect.m_position.x >= 790)
    {
        return direction::right;
    }
    else if(rect.m_position.y <= -20)
    {
        return direction::top;
    }
    else if(rect.m_position.y >= -785)
    {
        return direction::bottom;
    }
    else
    {
        return direction::noValue;
    }
}

void Game::changeMapManager()
{
   if(isAtTheEdge(m_warrior->getPos()) == direction::right
           && m_ml == map_1)
   {
        m_ml = map_2;
        Rectangle r = m_warrior->getPos();
        r.m_position.x = -15;
        m_warrior->setPos(r);
   }
   else if(isAtTheEdge(m_warrior->getPos()) == direction::left
           && m_ml == map_2)
   {
        m_ml = map_1;
        Rectangle r = m_warrior->getPos();
        r.m_position.x = 790;
        m_warrior->setPos(r);
   }
   else
   {
       loadNewZone();
   }
}

void Game::setMapLoad(const MapLoad m)
{
   m_ml = m;
}

MapLoad Game::getMapLoad() const
{
    return m_ml;
}

void Game::loadNewZone()
{
    if(m_map[map_1]->isInOutZone(m_warrior->getPos(), 0)
            && m_ml == map_1)
    {
        m_ml = instance1;
        Rectangle r = m_warrior->getPos();
        r.m_position = Vec2<int>(389, 684);
        m_warrior->setPos(r);
    }
    if(m_map[instance1]->isInOutZone(m_warrior->getPos(), 0)
            && m_ml == instance1)
    {
        m_ml = map_1;
        Rectangle r = m_warrior->getPos();
        r.m_position = Vec2<int>(591, 405);
        m_warrior->setPos(r);
    }

}

void Game::eventTouch(const char touch)
{
    if(m_status == run)
    {
        switch (touch)
        {
            case 'z' :
                touchZ();
                break;

            case 'q' :
                touchQ();
                break;

            case 's' :
                touchS();
                break;

            case 'd' :
                touchD();
                break;

            case 'f':
                touchF();
                break;

            case 'c':
                touchC();
                break;

            case ' ':
                touchSpace();
                break;
        }
    }

}

void Game::ennemyManager()
{
    switch (m_ml)
    {
    case map_1:
        for (int i=0;i<4;i++)
        {
            getEnemy(i,map_1).enemyPattern(getPlayer());
        }
        break;

    case map_2:
        for (int i=0;i<4;i++)
        {
            getEnemy(i,map_2).enemyPattern(getPlayer());
        }
        break;
    case instance1:
        for (int i=0;i<4;i++)
        {
            getEnemy(i,instance1).enemyPattern(getPlayer());
        }

    default:
        break;
    }
}

unsigned int Game::getNbMap() const
{
    return m_nbMap;
}

Menu &Game::getInventory() const
{
    return *m_inventory;
}

void Game::heal()
{
    unsigned int temp =  m_warrior->getHealth();
    temp += 10;
    m_warrior->setHealth(temp);
    std::cout<<"presssssssss"<<std::endl;
}

Map &Game::getMap1(unsigned int indice) const
{
    return *m_map[indice];
}


bool Game::collisionManager(Rectangle & posToModif,
           const Rectangle* tabPosobstacle, const unsigned int sizeTab,
           const direction::Type d)
{
    bool isNotInDecor = true;
    unsigned int indice = 0;
    Rectangle temp = posToModif;
    temp.m_position.y += 2 * temp.m_dimension.y / 3;
    temp.m_dimension.y /= 3;
    for(unsigned int i = 0; i < sizeTab && isNotInDecor; i++)
    {
        if(temp.in(tabPosobstacle[i]))
        {
            isNotInDecor = false;
            indice = i;
        }
    }
    if(isNotInDecor)
    {
        return true;
    }
    else
    {
        Rectangle r = posToModif;
        switch (d)
        {
            case direction::top:
                r.m_position += bottom;
                posToModif = r;
                break;

            case direction::left:
                r.m_position += right;
                posToModif = r;
                break;

            case direction::bottom:
                r.m_position += top;
                posToModif = r;
                break;

            case direction::right:
                r.m_position += left;
                posToModif = r;
                break;
        }
        while (temp.in(tabPosobstacle[indice]))
        {
            switch (d)
            {
                case direction::top:
                    r.m_position += bottom;
                    posToModif = r;

                    break;

                case direction::left:
                    r.m_position += right;
                    posToModif = r;
                    break;

                case direction::bottom:
                    r.m_position += top;
                    posToModif = r;
                    break;

                case direction::right:
                    r.m_position += left;
                    posToModif = r;
                    break;
            }
            temp.m_position = posToModif.m_position;
        }
        if(d == direction::top) // Pour "contrer" un bug, corriger le bug si le temps à la place de ce bricolage
        {
            Vec2<int> v = posToModif.m_dimension;
            v.y /= 3;
            v.y *= 2; // On divise par 2/3
            v.x = 0;
            Rectangle r = posToModif;
            r.m_position -= v;
            posToModif = r;
        }
        return false;
    }
}


Player &Game::getPlayer() const
{
    return *m_warrior;
}

Object &Game::getObject(unsigned int indice,MapLoad ml) const
{
    switch(ml)
    {
    case 0:
        return *m_tabObjectMap1[indice];

    case 1:
        return *m_tabObjectMap2[indice];
        break;

    default:
        break;
    }
}

Enemy &Game::getEnemy(unsigned int indice,MapLoad ml) const
{
    switch(ml)
    {
    case 0:
        return *m_tabEnemyMap1[indice];

    case 1:
        return *m_tabEnemyMap2[indice];
        break;
    case 2:
        return *m_tabEnemyInstance[indice];
        break;
    default:
        break;
    }
}

Rectangle &Game::getAllEnemyPos(const Enemy *tabEnemy, unsigned int sizeTab)
{
    delete m_tabPosEnemy;
    m_tabPosEnemy = new Rectangle[sizeTab];
    for (unsigned int i=0;i<sizeTab;i++)
    {
        m_tabPosEnemy[i] = Rectangle(tabEnemy->getPos());
    }
    return *m_tabPosEnemy;
}

Enemy *Game::getAllEnemy(MapLoad ml) const
{
    switch(ml)
    {
    case 0:
        return *m_tabEnemyMap1;
        break;
    case 1:
        return *m_tabEnemyMap2;
        break;
    default:
        break;
    }
}

void Game::touchZ()
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                        m_map[m_ml]->getNbDecor() ,direction::top))
    {
        m_warrior->move(top);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                     m_map[m_ml]->getNbDecor() ,direction::top);
    m_warrior->updateRangeTop();
    changeMapManager();
}

void Game::touchQ()
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                        m_map[m_ml]->getNbDecor() ,direction::left))
        // On test une avant de bouger si ok alors on bouge
    {
        m_warrior->move(left);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                     m_map[m_ml]->getNbDecor() ,direction::left);
    // Puis on restest après avoir bouger, car il est possible d'être dans le décor après le déplacement
    m_warrior->updateRangeLeft();
    changeMapManager();
}

void Game::touchS()
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                        m_map[m_ml]->getNbDecor() ,direction::bottom))
    {
        m_warrior->move(bottom);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                     m_map[m_ml]->getNbDecor() ,direction::bottom);
    m_warrior->updateRangeBottom();
    changeMapManager();
}

void Game::touchD()
{

    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                        m_map[m_ml]->getNbDecor() ,direction::right))
    {
        m_warrior->move(right);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(),
                     m_map[m_ml]->getNbDecor() ,direction::right);
    m_warrior->updateRangeRight();
    changeMapManager();
}

void Game::touchF()
{
    switch(m_ml)
    {
    case 0:
        m_warrior->Loot(*m_tabObjectMap1,3);
        break;
    case 1:
        m_warrior->Loot(*m_tabObjectMap2,2);
        break;
    default:
        break;
    }
}

void Game::touchC()
{
    m_warrior->getPlayerStats();
}

void Game::touchSpace()
{
    switch(m_ml)
    {
    case 0:
        for(int i=0;i<4;i++)
        {
            m_warrior->attack(*m_tabEnemyMap1[i]);
        }
    case 1:
        for(int i=0;i<4;i++)
        {
            m_warrior->attack(*m_tabEnemyMap2[i]);
        }
        break;
    case 2:
        for(int i=0;i<4;i++)
        {
            m_warrior->attack(*m_tabEnemyInstance[i]);
        }
    default:
        break;
    }
}


void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0, ptrOnLauchGame, *this, GameStatus::run, mousePos);
    m_inventory->open(mousePos, m_status);
    m_inventory->close(mousePos, m_status);
    m_inventory->listenEvent(0, ptrOnHeal, *this, mousePos);
    std::cout<<m_warrior->getHealth()<<std::endl;
    std::cout<<m_inventory->getChoice(0).getIsLoad()<<std::endl;
}


