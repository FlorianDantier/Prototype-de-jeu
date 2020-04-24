#include "Game.h"
#include <cassert>

Game::Game() : m_home(nullptr), m_status(GameStatus::home), map1(nullptr)
{
    ptrONsetStatus = &Game::setStatus;
    Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
    m_home = new Menu(2, true, true, notLoad, notLoad); // Le menu "home" est une exception dans le sens où il n'y aura pas de bouton pour ouvir ou fermer ce menu
    m_home->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);
    Rectangle warPos(windowSize.x/2,windowSize.y/2,30,30);
    m_warrior = new Player("Bob",warrior,warPos,100,1);

    map1 = new Map(1);
    assert(map1 != nullptr);

    Rectangle decor1(354, 178, 64, 144);
    map1->setDecor(0, decor1);

}

Game::~Game()
{
    delete m_home;
    m_home = nullptr;
    delete m_warrior;
    m_warrior = nullptr;
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

Player &Game::getPlayer() const
{
    return *m_warrior;
}

void Game::touchZ()
{
    if(!m_warrior->getPos().in(map1->getDecor(0)))
        m_warrior->move(top);

    if(m_warrior->getPos().in(map1->getDecor(0)))
    {
        m_warrior->move(bottom);
        while (m_warrior->getPos().in(map1->getDecor(0)))
        {
            m_warrior->move(bottom);
        }
    }
}

void Game::touchQ()
{
    if(!m_warrior->getPos().in(map1->getDecor(0)))
        m_warrior->move(left);

    if(m_warrior->getPos().in(map1->getDecor(0)))
    {
        m_warrior->move(right);
        while (m_warrior->getPos().in(map1->getDecor(0)))
        {
            m_warrior->move(right);
        }

    }
}

void Game::touchS()
{
    if(!m_warrior->getPos().in(map1->getDecor(0)))
        m_warrior->move(bottom);

    if(m_warrior->getPos().in(map1->getDecor(0)))
    {
        m_warrior->move(top);
        while (m_warrior->getPos().in(map1->getDecor(0)))
        {
            m_warrior->move(top);
        }

    }
}

void Game::touchD()
{
    if(!m_warrior->getPos().in(map1->getDecor(0)))
        m_warrior->move(right);

    if(m_warrior->getPos().in(map1->getDecor(0)))
    {
        m_warrior->move(left);
        while (m_warrior->getPos().in(map1->getDecor(0)))
        {
            m_warrior->move(left);
        }

    }
}

void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0, ptrONsetStatus, *this, GameStatus::run, mousePos);
}


