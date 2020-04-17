#include "Game.h"

Game::Game() : m_home(nullptr)
{
    ptrONsetStatus = &Game::setStatus;
    Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
    m_home = new Menu(2, true, true, notLoad, notLoad);
    m_home->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);

}

Game::~Game()
{
    delete m_home;
    m_home = nullptr;
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

void Game::touchZ()
{

}

void Game::touchQ()
{

}

void Game::touchS()
{

}

void Game::touchD()
{

}

void Game::mouseLeftClick(const Vec2<int> &mousePos)
{
    getHome().listenEvent(0,ptrONsetStatus, *this, GameStatus::run, mousePos);
}


