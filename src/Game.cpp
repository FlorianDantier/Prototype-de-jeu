#include "Game.h"
#include <cassert>

Game::Game() : m_home(nullptr), m_status(GameStatus::home)
{
    m_nbMap = 2;
    for(unsigned int i = 0; i < m_nbMap; i++)
    {
        m_map[i] = nullptr;
    }
    ptrOnLauchGame = &Game::launchGame;
    Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
    m_home = new Menu(1, true, true, notLoad, notLoad); // Le menu "home" est une exception dans le sens où il n'y aura pas de bouton pour ouvir ou fermer ce menu
    m_home->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);

    m_ml = map_1;
    //=============== Création des maps==================
    m_map[0] = new Map(73, 2, 0);

    assert(m_map[map_1] != nullptr);
    m_map[map_2] = new Map(104, 1, 1);
    assert(m_map[map_2] != nullptr);
    // =========Fin de création des maps================
    // =========Ajout du Player==========
    Rectangle warPos(windowSize.x / 2, windowSize.y / 2, 25, 34);
    m_warrior = new Player("Bob", warrior, warPos, 100, 1);

    // =========Fin ajout du Player==========

    // =========Ajout des Objets dans les maps=========
    //pour la map1
    m_tabObjectMap1[0] = new Object("Health Potion",other,500,Rectangle(217,663,20,20),50,false,true);
    m_tabObjectMap1[1] = new Object("Hell's Sword",weapon,500,Rectangle(600,574,20,20),50,false,true);
    m_tabObjectMap1[2] = new Object("Hell's Armor",armor,500,Rectangle(475,310,20,20),20,false,true);
    //Fin pour la map1

    //pour la map2
    m_tabObjectMap2[0] = new Object("Health Potion",other,500,Rectangle(570,50,20,20),50,false,true);
    m_tabObjectMap2[1] = new Object("Health Potion",other,500,Rectangle(700,650,20,20),50,false,true);
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

    //pour la map2
    m_tabEnemyMap2[0] = new Enemy(elite,humanoid,Rectangle(255,600,32,64),
                                  500,1,verticalTop,false);
    m_tabEnemyMap2[1] = new Enemy(elite,humanoid,Rectangle(550,370,32,64),
                                  500,1,horizontalRight,false);
    m_tabEnemyMap2[2] = new Enemy(boss,humanoid,Rectangle(500,600,50,100),
                                  2000,1,horizontalLeft,false);
    m_tabEnemyMap2[3] = new Enemy(sbire,humanoid,Rectangle(150,150,32,64),
                                  200,1,horizontalLeft,false);
    //Fin pour la map2

    // =========Fin Ajout des ennemis dans les maps=========


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
   if(isAtTheEdge(m_warrior->getPos()) == direction::right && m_ml == map_1)
   {
        m_ml = map_2;
        Rectangle r = m_warrior->getPos();
        r.m_position.x = -15;
        m_warrior->setPos(r);
   }
   else if(isAtTheEdge(m_warrior->getPos()) == direction::left && m_ml == map_2)
   {
        m_ml = map_1;
        Rectangle r = m_warrior->getPos();
        r.m_position.x = 790;
        m_warrior->setPos(r);
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
    if(m_map[0]->isInOutZone(m_warrior->getPos(), 0))
    {
        std::cout<<"Marche"<<std::endl;
        //m_ml = instance1;
    }
}

Map &Game::getMap1(unsigned int indice) const
{
    return *m_map[indice];
}

void Game::eventManagers()
{
    if(m_status == GameStatus::run) // En partie "classique"
    {

    }
    else if(m_status == GameStatus::home) // Au lancement du jeu, sur le menu d'accueil
    {

    }
    else if(m_status == GameStatus::standBy) // Jeu en pause, par exemple si l'on ouvre l'inventaire
    {

    }
}

bool Game::collisionManager(Rectangle & posToModif, const Rectangle* tabPosobstacle, const unsigned int sizeTab, const direction::Type d)
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

    default:
        break;
    }
}

void Game::touchZ(MapLoad ml)
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::top))
    {
        m_warrior->move(top);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::top);
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveTop(*m_tabEnemyMap1,4);
        break;
    case 1:
        m_warrior->updatePlayerMoveTop(*m_tabEnemyMap2,4);
        break;
    default:
        break;
    }

    changeMapManager();
}

void Game::touchQ(MapLoad ml)
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::left)) // On test une avant de bouger si ok alors on bouge
    {
        m_warrior->move(left);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::left); // Puis on restest après avoir bouger, car il est possible d'être dans le décor après le déplacement
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveLeft(*m_tabEnemyMap1,4);
        break;
    case 1:
        m_warrior->updatePlayerMoveLeft(*m_tabEnemyMap2,4);
        break;
    default:
        break;
    }
    changeMapManager();
}

void Game::touchS(MapLoad ml)
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::bottom))
    {
        m_warrior->move(bottom);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::bottom);
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveBottom(*m_tabEnemyMap1,4);
        break;
    case 1:
        m_warrior->updatePlayerMoveBottom(*m_tabEnemyMap2,4);
        break;
    default:
        break;
    }
    changeMapManager();
}

void Game::touchD(MapLoad ml)
{
    if(collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::right))
    {
        m_warrior->move(right);
    }
    collisionManager(m_warrior->getPos(), m_map[m_ml]->getAllDecor(), m_map[m_ml]->getNbDecor() ,direction::right);
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveRight(*m_tabEnemyMap1,4);
        break;
    case 1:
        m_warrior->updatePlayerMoveRight(*m_tabEnemyMap2,4);
        break;
    default:
        break;
    }
    changeMapManager();
}

void Game::touchF(MapLoad ml)
{
    switch(ml)
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

void Game::touchSpace(MapLoad ml)
{
    switch(ml)
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
    default:
        break;
    }
}


void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0, ptrOnLauchGame, *this, GameStatus::run, mousePos);
}


