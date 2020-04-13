#include "Button.h"

Button::Button()
{
    m_isLoad = false;
    // Constructeur d'image et rectangle appelé (constructeur par défaut)
}

Button::Button(const Rectangle & position, bool isLoad)
{
    m_position = position;
    m_isLoad = isLoad;
}

Rectangle Button::getPosition() const
{
    return m_position;
}

bool Button::isPressed(Vec2<int> mousePos)
{
    if(m_isLoad)
    {
        if(m_position.in(mousePos))
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

