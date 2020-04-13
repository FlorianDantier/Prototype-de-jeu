#include "Menu.h"
#include <cassert>



void Menu::isLoadButton()
{
    if(m_isLoad)
    {
        if(m_isOpen)
        {
            for(unsigned int i = 0; i < m_nbChoices; i++)
            {
                m_choices[i].m_isLoad = true;
            }
            m_closeButton.m_isLoad = true;
            m_openButton.m_isLoad = false;
        }
        else
        {
            for(unsigned int i = 0; i < m_nbChoices; i++)
            {
                m_choices[i].m_isLoad = false;
            }
            m_closeButton.m_isLoad = false;
            m_openButton.m_isLoad = true;
        }
    }
    else
    {
        for(unsigned int i = 0; i < m_nbChoices; i++)
        {
            m_choices[i].m_isLoad = false;
        }
        m_openButton.m_isLoad = false;
        m_closeButton.m_isLoad = false;
    }
}

void Menu::setIsOpen(const bool isOpen)
{
    m_isOpen = isOpen;
    isLoadButton();
}

bool Menu::getIsOpen() const
{
    return m_isOpen;
}

Menu::Menu()
{
    m_isOpen = false;
    m_choices = nullptr;
    m_nbChoices = 0;
}

Menu::Menu(int nbButton, bool isOpen, bool isLoad)
{
    m_isOpen = isOpen;
    m_isLoad = isLoad;
    assert(nbButton > 0);
    m_nbChoices = nbButton;
    m_choices = new Button[m_nbChoices];
    isLoadButton();
}

void Menu::mouseLeftClick(const Vec2<int> & leftClick)
{
    open(leftClick);
    close(leftClick);
}

void Menu::open(const Vec2<int> & leftClick)
{
   if(m_isOpen == false && m_openButton.isPressed(leftClick))
   {
       m_isOpen = true;
       std::cout<<"open pressed\n";
       isLoadButton();
   }
}

void Menu::close(const Vec2<int> & leftClick)
{
    if(m_isOpen == true && m_closeButton.isPressed(leftClick))
    {
        m_isOpen = false;
        std::cout<<"close pressed\n";
        isLoadButton();
    }
}


//void Menu::display(SDL_Renderer *renderer)
//{
//    if(m_isLoad)
//    {
//        if(m_isOpen)
//        {
//            m_background.display(renderer);
//            for(unsigned int i = 0; i < m_nbChoices; i++)
//            {
//                m_choices[i].display(renderer);
//            }
//            m_closeButton.display(renderer);
//        }
//        else
//        {
//            m_openButton.display(renderer);
//        }
//    }
//}

void Menu::setChoice(const Button &btn, const unsigned int indice)
{
    assert(indice >= 0 && indice < m_nbChoices);
    m_choices[indice] = btn;
    isLoadButton();
    // à changer, à voir dans l'opérateur = ?
}

Button &Menu::getChoice(const unsigned int indice) const
{
    assert(indice >= 0 && indice < m_nbChoices);
    return m_choices[indice];
}

void Menu::setOpenButton(const Button &b)
{
    m_openButton = b;
}

Button Menu::getOpenButton() const
{
    return m_openButton;
}

void Menu::setCloseButton(const Button &b)
{
    m_closeButton = b;
}

Button Menu::getCloseButton() const
{
    return m_closeButton;
}

Button &Menu::listenEvent(const unsigned int indice)
{
    assert(indice >= 0 && indice < m_nbChoices);
    return m_choices[indice];
}

void Menu::setIsLoad(const bool isLoad)
{
    m_isLoad = isLoad;
    isLoadButton();
}

bool Menu::getIsLoad() const
{
    return m_isLoad;
}

Menu::~Menu()
{
    delete [] m_choices;
    m_choices = nullptr;
}
