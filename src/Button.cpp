#include "Button.h"

Button::Button()
{
    m_isHover = false;
    // Constructeur d'image et rectangle appelé (constructeur par défaut)
}

Button::Button(const Rectangle &  position, std::string pathImage, SDL_Renderer* renderer) :
    m_image(pathImage, position, Vec2<unsigned int>(640, 480), renderer)
{
    m_position = position;
    m_isHover = false;
    m_isPressed = false;
}

void Button::imageForHover()
{
    if(m_isHover)
    {
        // On changera d'image(plus en relief ou en surbrillance)
    }
}

void Button::imageForOtherCase()
{
    if(!m_isHover)
    {
        // On changera d'image
    }
}

void Button::display(SDL_Renderer *renderer)
{
    m_image.display(renderer);
}


void Button::curseurIsHover(const SDL_Event &event)
{
    Vec2<int> point(event.button.x, event.button.y);
    if(m_position.in(point))
        m_isHover = true;
    else
        m_isHover = false;
}

void Button::isClick(const SDL_Event &event)
{
    if(m_isHover && event.type == SDL_MOUSEBUTTONDOWN)
        m_isPressed = true;
}
