#include "Menu.h"


void Menu::isLoadButton()
{
    if(m_isLoad)
    {
        if(m_isOpen)
        {
            for(unsigned int i = 0; i < m_nbChoices; i++)
            {
                m_choices[i].setIsLoad(true);
            }
            m_closeButton->setIsLoad(true);
            m_openButton->setIsLoad(false);
        }
        else
        {
            for(unsigned int i = 0; i < m_nbChoices; i++)
            {
                m_choices[i].setIsLoad(false);
            }
            m_closeButton->setIsLoad(false);
            m_openButton->setIsLoad(true);
        }
    }
    else
    {
        for(unsigned int i = 0; i < m_nbChoices; i++)
        {
            m_choices[i].setIsLoad(false);
        }
        m_openButton->setIsLoad(false);
        m_closeButton->setIsLoad(false);
    }
}

Menu& Menu::operator=(const Menu &copie)
{
    if(this != &copie)
    {
        delete [] m_choices;
        delete m_openButton;
        delete m_closeButton;
        delete m_position;

        m_position = new Rectangle(*(copie.m_position));
        m_openButton = new Button(*(copie.m_openButton));
        m_closeButton = new Button(*(copie.m_closeButton));
        m_choices = new Button[copie.m_nbChoices];
        for(unsigned int i = 0; i < copie.m_nbChoices; i++)
        {
            m_choices[i] = copie.m_choices[i];
        }
    }

    return *this;
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
    m_openButton = nullptr;
    m_closeButton = nullptr;
    m_nbChoices = 0;
}

Menu::Menu(unsigned int nbButton, const Rectangle & position, bool isOpen, bool isLoad,
           const Button &open, const Button &close)
           : m_openButton(nullptr), m_closeButton(nullptr), m_position(nullptr)
{
    m_position = new Rectangle(position);
    assert(m_position != nullptr);
    m_isOpen = isOpen;
    m_isLoad = isLoad;
    assert(nbButton > 0);
    m_nbChoices = nbButton;
    m_choices = new Button[m_nbChoices];

    m_openButton = new Button(open);
    m_closeButton = new Button(close);

    isLoadButton();
}

void Menu::open(const Vec2<int> & leftClick, GameStatus & gs)
{
   if(m_isOpen == false && m_openButton->isPressed(leftClick))
   {
       m_isOpen = true;
       std::cout<<"open pressed\n";
       isLoadButton();
       gs = standBy;
   }
}

void Menu::close(const Vec2<int> & leftClick, GameStatus & gs)
{
    if(m_isOpen == true && m_closeButton->isPressed(leftClick))
    {
        m_isOpen = false;
        std::cout<<"close pressed\n";
        isLoadButton();
        gs = run;
    }
}

void Menu::setChoice(const Button &btn, const unsigned int indice)
{
    assert(indice >= 0 && indice < m_nbChoices);
    m_choices[indice] = btn;
    isLoadButton();
}

Button& Menu::getChoice(const unsigned int indice) const
{
    assert(indice >= 0 && indice < m_nbChoices);
    return m_choices[indice];
}

void Menu::setOpenButton(const Button &b)
{
    if(m_openButton != nullptr)
    {
        delete m_openButton;
    }

    m_openButton = new Button(b);
}

Button& Menu::getOpenButton() const
{
    return *m_openButton;
}

void Menu::setCloseButton(const Button &b)
{
    if(m_closeButton != nullptr)
    {
        delete m_closeButton;
    }

    m_closeButton = new Button(b);
}

Button& Menu::getCloseButton() const
{
    // Vérifier si diff de nullptr ?
    return *m_closeButton;
}

void Menu::setIsLoad(const bool isLoad)
{
    m_isLoad = isLoad;
    isLoadButton();
}

Rectangle &Menu::getPosition() const
{
    return *m_position;
}

bool Menu::getIsLoad() const
{
    return m_isLoad;
}

Menu::~Menu()
{
    delete [] m_choices;
    m_choices = nullptr;

    delete m_openButton;
    delete m_closeButton;
}
