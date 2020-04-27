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
    map[0] = new Map(17);
    assert(map[0] != nullptr);


    Rectangle statue1 = Rectangle(504, 552, 48, 48);
    Rectangle statue2 = Rectangle(655, 550, 48, 48);

    Rectangle temple[3];
    temple[0] = Rectangle(553, 276, 99, 110);
    temple[1] = Rectangle(554, 276, 24, 224);
    temple[2] = Rectangle(628, 276, 24, 224);


    Rectangle mur[10];
    mur[0] = Rectangle(0, 758, 256, 27);
    mur[1] = Rectangle(300, 707, 136, 27);
    mur[2] = Rectangle(476, 657, 178, 27);
    mur[3] = Rectangle(723, 732, 77, 28);
    mur[4] = Rectangle(120, 550, 26, 83);
    mur[5] = Rectangle(105, 197, 40, 157);
    mur[6] = Rectangle(225, 0, 21, 103);
    mur[7] = Rectangle(0, 482, 78, 26);
    mur[8] = Rectangle(0, 434, 52, 15);
    mur[9] = Rectangle(0, 717, 52, 10);

    map[0]->setDecor(3, statue1);
    map[0]->setDecor(4, statue2);
    for(int i = 0; i < 3; i++)
    {
        map[0]->setDecor(i, temple[i]);
    }
    for(int i = 0; i < 10; i++)
    {
        map[0]->setDecor(i + 5, mur[i]);
    }

    Rectangle stone[2];
    stone[0] = Rectangle(727, 52, 73, 20);
    stone[1] = Rectangle(707, 0, 21, 51);

    map[0]->setDecor(15, stone[0]);
    map[0]->setDecor(16, stone[1]);


    map[1] = new Map(1);
    map[1]->setDecor(0, Rectangle(102, 327, 95, 70));
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
    /*m_tabEnemyMap1[0] = new Enemy(sbire,humanoid,Rectangle(400,50,25,40),
                                  *m_tabObjectMap1[0],*m_tabObjectMap1[2],150,1,horizontalLeft,false);
    m_tabEnemyMap1[1] = new Enemy(sbire,humanoid,Rectangle(550,150,25,40),
                                  *m_tabObjectMap1[0],*m_tabObjectMap1[2],150,1,horizontalLeft,false);
    m_tabEnemyMap1[2] = new Enemy(elite,humanoid,Rectangle(180,460,25,40),
                                  *m_tabObjectMap1[0],*m_tabObjectMap1[2],500,1,verticalBottom,true);
    m_tabEnemyMap1[3] = new Enemy(sbire,humanoid,Rectangle(400,550,25,40),
                                  *m_tabObjectMap1[0],*m_tabObjectMap1[0],200,1,verticalBottom,true);*/
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

Object &Game::getObject(unsigned int indice) const
{
    return *m_tabObjectMap1[indice];
}

void Game::touchZ()
{
    if(collisionManager(direction::top))
    {
        m_warrior->move(top);
    }
    collisionManager(direction::top);
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    changeMapManager();
}

void Game::touchQ()
{
    if(collisionManager(direction::left)) // On test une avant de bouger si ok alors on bouge
    {
        m_warrior->move(left);
    }
    collisionManager(direction::left); // Puis on restest après avoir bouger, car il est possible d'être dans le décor après le déplacement
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    changeMapManager();
}

void Game::touchS()
{
    if(collisionManager(direction::bottom))
    {
        m_warrior->move(bottom);
    }
    collisionManager(direction::bottom);
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    changeMapManager();
}

void Game::touchD()
{
    if(collisionManager(direction::right))
    {
        m_warrior->move(right);
    }
    collisionManager(direction::right);
    std::cout<<m_warrior->getPos().m_position.x<< " / "<<m_warrior->getPos().m_position.y<<std::endl;
    changeMapManager();
}


void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0, ptrOnLauchGame, *this, GameStatus::run, mousePos);
}


