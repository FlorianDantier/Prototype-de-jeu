#include "Button.h"
//aaaa

Button::Button() : m_position(nullptr), m_isLoad(false)
{

}

Button::Button(const Rectangle & position, bool isLoad) : m_position(nullptr), m_isLoad(isLoad)
{
    m_position = new Rectangle(position);
}

Button::Button(const Button &copie) : m_position(nullptr), m_isLoad(copie.m_isLoad)
{
    m_position = new Rectangle(*(copie.m_position));
}

Button::~Button()
{
    delete m_position;
    //    m_position = nullptr;
}

Button &Button::operator=(const Button &copie)
{    
    if(this != &copie)
    {
        m_isLoad = copie.m_isLoad;
        delete m_position;
        m_position = new Rectangle(*(copie.m_position));
    }
    return *this;
}

Rectangle& Button::getPosition() const
{
    return *m_position;
}

void Button::setIsLoad(const bool b)
{
    m_isLoad = b;
}

bool Button::getIsLoad() const
{
    return m_isLoad;
}

bool Button::isPressed(const Vec2<int> &mousePos)
{
    if(m_isLoad)
    {
        if(m_position->in(mousePos))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

