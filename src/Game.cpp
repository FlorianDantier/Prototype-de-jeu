#include "Game.h"

Game::Game() : m_home(nullptr)
{
    Button open(Rectangle(80, 50, windowSize.x - 80*2, 50), true);
    Button close(Rectangle(80, 50, windowSize.x - 80*2, 50), true);
    m_home = new Menu(1, true, true, open, close);
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
