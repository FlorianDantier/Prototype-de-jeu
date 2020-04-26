#include "Game.h"
#include <cassert>

Game::Game() : m_home(nullptr), m_status(GameStatus::home), map1(nullptr)
{
    ptrONsetStatus = &Game::setStatus;
    Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
    m_home = new Menu(2, true, true, notLoad, notLoad); // Le menu "home" est une exception dans le sens où il n'y aura pas de bouton pour ouvir ou fermer ce menu
    m_home->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);
    Rectangle warPos(windowSize.x / 2, windowSize.y / 2, 25, 34);
    m_warrior = new Player("Bob", warrior, warPos, 100, 1);

    //=============== Création des maps==================
    map1 = new Map(17);
    assert(map1 != nullptr);


    Rectangle statue1 = Rectangle(504, 552, 48, 48);
    Rectangle statue2 = Rectangle(655, 550, 48, 48);

    Rectangle temple[3];
    temple[0] = Rectangle(553, 276, 99, 95);
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

    map1->setDecor(3, statue1);
    map1->setDecor(4, statue2);
    for(int i = 0; i < 3; i++)
    {
        map1->setDecor(i, temple[i]);
    }
    for(int i = 0; i < 10; i++)
    {
        map1->setDecor(i + 5, mur[i]);
    }

    Rectangle stone[2];
    stone[0] = Rectangle(727, 52, 73, 20);
    stone[1] = Rectangle(707, 0, 21, 51);

    map1->setDecor(15, stone[0]);
    map1->setDecor(16, stone[1]);
    // =========Fin de création des maps================

}

Game::~Game()
{
    delete m_home;
    m_home = nullptr;

    delete m_warrior;
    m_warrior = nullptr;

    delete map1;
    map1 = nullptr;
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
    std::cout<<"marche"<<std::endl;
    m_status = gs;
}


Map &Game::getMap1() const
{
    return *map1;
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
    for(unsigned int i = 0; i < map1->getNbDecor() && isNotInDecor; i++)
    {
        if(m_warrior->getPos().in(map1->getDecor(i)))
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
        while (m_warrior->getPos().in(map1->getDecor(indice)))
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
        }
        return false;
    }
}

Player &Game::getPlayer() const
{
    return *m_warrior;
}

void Game::touchZ()
{
    if(collisionManager(direction::top))
    {
        m_warrior->move(top);
    }
    collisionManager(direction::top);
}

void Game::touchQ()
{
    if(collisionManager(direction::left)) // On test une avant de bouger si ok alors on bouge
    {
        m_warrior->move(left);
    }
    collisionManager(direction::left); // Puis on restest après avoir bouger, car il est possible d'être dans le décor après le déplacement
}

void Game::touchS()
{
    if(collisionManager(direction::bottom))
    {
        m_warrior->move(bottom);
    }
    collisionManager(direction::bottom);
}

void Game::touchD()
{
    if(collisionManager(direction::right))
    {
        m_warrior->move(right);
    }
    collisionManager(direction::right);
}

void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0, ptrONsetStatus, *this, GameStatus::run, mousePos);
    getHome().getChoice(0).setIsLoad(false);
}


