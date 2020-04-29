#include "Game.h"
#include <cassert>

Game::Game() : m_home(nullptr), m_status(GameStatus::home)
{
    nbMap = 2;
    for(unsigned int i = 0; i < nbMap; i++)
    {
        map[i] = nullptr;
    }
    ptrOnLauchGame = &Game::launchGame;
    Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
    m_home = new Menu(1, true, true, notLoad, notLoad); // Le menu "home" est une exception dans le sens où il n'y aura pas de bouton pour ouvir ou fermer ce menu
    m_home->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);
    Rectangle warPos(windowSize.x / 2, windowSize.y / 2, 25, 34);
    m_warrior = new Player("Bob", warrior, warPos, 100, 1);

    ml = map_1;
    //=============== Création des maps==================
    map[0] = new Map(73, 0);

    assert(map[map_1] != nullptr);


    map[map_2] = new Map(104, 1);
    assert(map[map_2] != nullptr);



































    // =========Fin de création des maps================

    // =========Ajout des Objets dans les maps=========
    //pour la map1
    m_tabObjectMap1[0] = new Object("Health Potion",other,500,Rectangle(217,663,30,30),50,false,true);
    m_tabObjectMap1[1] = new Object("Hell's Sword",weapon,500,Rectangle(600,574,30,30),50,false,true);
    m_tabObjectMap1[2] = new Object("Hell's Armor",armor,500,Rectangle(475,310,30,30),20,false,true);
    //Fin pour la map1

    // =========Fin Ajout des objets dans les maps=========

    // =========Ajout des ennemis dans les maps=========
    //pour la map1
    m_tabEnemyMap1[0] = new Enemy(sbire,humanoid,Rectangle(350,5,75,150),
                                  150,1,horizontalLeft,false);
    m_tabEnemyMap1[1] = new Enemy(sbire,humanoid,Rectangle(550,150,75,150),
                                  150,1,horizontalRight,false);
    m_tabEnemyMap1[2] = new Enemy(elite,humanoid,Rectangle(180,350,100,200),
                                  500,1,verticalBottom,true);
    m_tabEnemyMap1[3] = new Enemy(sbire,humanoid,Rectangle(400,550,75,150),
                                  200,1,verticalTop,true);
    //Fin pour la map1

    // =========Fin Ajout des ennemis dans les maps=========


}

Game::~Game()
{
    delete m_home;
    m_home = nullptr;

    delete m_warrior;
    m_warrior = nullptr;

    for(unsigned int i = 0; i < nbMap; i++)
    {
        delete map[i];
        map[i] = nullptr;
    }
    /*for(unsigned int i = 0; i < 3; i++)
    {
        delete m_tabObjectMap1[i];
        m_tabObjectMap1[i] = nullptr;
    }
    for(unsigned int i = 0; i < 4; i++)
    {
        delete m_tabEnemyMap1[i];
        m_tabEnemyMap1[i] = nullptr;
    }*/
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
   if(isAtTheEdge(m_warrior->getPos()) == direction::right && ml == map_1)
   {
        ml = map_2;
        Rectangle r = m_warrior->getPos();
        r.m_position.x = -15;
        m_warrior->setPos(r);
   }
   else if(isAtTheEdge(m_warrior->getPos()) == direction::left && ml == map_2)
   {
        ml = map_1;
        Rectangle r = m_warrior->getPos();
        r.m_position.x = 790;
        m_warrior->setPos(r);
   }
}

void Game::setMapLoad(const MapLoad m)
{
    ml = m;
}

MapLoad Game::getMapLoad() const
{
    return ml;
}

Map &Game::getMap1(unsigned int indice) const
{
    return *map[indice];
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

bool Game::collisionManager(const direction::Type d)
{
    bool isNotInDecor = true;
    unsigned int indice = 0;
    Rectangle temp = m_warrior->getPos();
    temp.m_position.y += 2 * temp.m_dimension.y / 3;
    temp.m_dimension.y /= 3;
    for(unsigned int i = 0; i < map[ml]->getNbDecor() && isNotInDecor; i++)
    {
        if(temp.in(map[ml]->getDecor(i)))
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
        Rectangle r = m_warrior->getPos();
        switch (d)
        {
            case direction::top:
                r.m_position += bottom;
                m_warrior->setPos(r);
                break;

            case direction::left:
                r.m_position += right;
                m_warrior->setPos(r);
                break;

            case direction::bottom:
                r.m_position += top;
                m_warrior->setPos(r);
                break;

            case direction::right:
                r.m_position += left;
                m_warrior->setPos(r);
                break;
        }
        while (temp.in(map[ml]->getDecor(indice)))
        {
            switch (d)
            {
                case direction::top:
                    r.m_position += bottom;
                    m_warrior->setPos(r);

                    break;

                case direction::left:
                    r.m_position += right;
                    m_warrior->setPos(r);
                    break;

                case direction::bottom:
                    r.m_position += top;
                    m_warrior->setPos(r);
                    break;

                case direction::right:
                    r.m_position += left;
                    m_warrior->setPos(r);
                    break;
            }
            temp.m_position = m_warrior->getPos().m_position;
        }
        if(d == direction::top) // Pour "contrer" un bug, corriger le bug si le temps à la place de ce bricolage
        {
            Vec2<int> v = m_warrior->getPos().m_dimension;
            v.y /= 3;
            v.y *= 2; // On divise par 2/3
            v.x = 0;
            Rectangle r = m_warrior->getPos();
            r.m_position -= v;
            m_warrior->setPos(r);
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
        break;

    default:
        break;
    }
}

void Game::touchZ(MapLoad ml)
{
    if(collisionManager(direction::top))
    {
        m_warrior->move(top);
    }
    collisionManager(direction::top);
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveTop(*m_tabEnemyMap1,4);
        break;
    case 1:
        break;
    default:
        break;
    }

    changeMapManager();
}

void Game::touchQ(MapLoad ml)
{
    if(collisionManager(direction::left)) // On test une avant de bouger si ok alors on bouge
    {
        m_warrior->move(left);
    }
    collisionManager(direction::left); // Puis on restest après avoir bouger, car il est possible d'être dans le décor après le déplacement
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveLeft(*m_tabEnemyMap1,4);
        break;
    case 1:
        break;
    default:
        break;
    }
    changeMapManager();
}

void Game::touchS(MapLoad ml)
{
    if(collisionManager(direction::bottom))
    {
        m_warrior->move(bottom);
    }
    collisionManager(direction::bottom);
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveBottom(*m_tabEnemyMap1,4);
        break;
    case 1:
        break;
    default:
        break;
    }
    changeMapManager();
}

void Game::touchD(MapLoad ml)
{
    if(collisionManager(direction::right))
    {
        m_warrior->move(right);
    }
    collisionManager(direction::right);
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    switch(ml)
    {
    case 0:
        m_warrior->updatePlayerMoveRight(*m_tabEnemyMap1,4);
        break;
    case 1:
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
        if (ml==map_1)
        {
            m_warrior->Loot(*m_tabObjectMap1,3);
        }
        break;
    case 1:
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
        break;
    default:
        break;
    }
}


void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0, ptrOnLauchGame, *this, GameStatus::run, mousePos);
}


