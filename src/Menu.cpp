#include "Menu.h"
#include <cassert>

Menu::Menu()
{
    m_isOpen = false;
    m_choices = nullptr;
    m_nbChoices = 0;
}

Menu::Menu(int nbButton, const Rectangle &position, const std::string & pathImageBackground, SDL_Renderer* renderer, bool isOpen) :
    m_background(pathImageBackground, position, Vec2<unsigned int>(640, 480), renderer)
{
    m_isOpen = isOpen;
    assert(nbButton > 0);
    m_nbChoices = nbButton;
    m_choices = new Button[m_nbChoices];
}

void Menu::display(SDL_Renderer *renderer)
{
    m_background.display(renderer);
    for(unsigned int i = 0; i < m_nbChoices; i++)
        m_choices[i].display(renderer);
}

void Menu::setChoice(const Button &btn, unsigned int indice)
{
    assert(indice >= 0 && indice < m_nbChoices);
    m_choices[indice] = btn;
}

Button &Menu::getChoice(const unsigned int indice)
{
    assert(indice >= 0 && indice < m_nbChoices);
    return m_choices[indice];
}

Menu::~Menu()
{
    delete [] m_choices;
    m_choices = nullptr;
}
