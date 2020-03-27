#ifndef BUTTON_H
#define BUTTON_H

#include "Rectangle.h"
#include "Image.h"
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
/**
 * @brief Cette classe permet de créer un bouton
 */
class Button
{
private:
    Image m_image;
    Rectangle m_position;
    bool m_isHover;
    bool m_isPressed;


    void curseurIsHover(const SDL_Event & event);
    void isClick(const SDL_Event & event);
    template<typename nameClass, typename returnType>
    void actionOnClick(returnType (nameClass::*ptr)(), nameClass & object) const;

    template<typename nameClass, typename returnType, typename arg>
    void actionOnClick(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct) const;

public:
    Button();
    Button(const Rectangle & position, const std::string & pathImage, SDL_Renderer *renderer);
    void imageForOtherCase();

    template<typename nameClass, typename returnType>
    void eventButton(returnType (nameClass::*ptr)(), nameClass & object, const SDL_Event & event);

    template<typename nameClass, typename returnType, typename arg>
    void eventButton(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct ,const SDL_Event & event);


    void display(SDL_Renderer* renderer);
    // A voir pour une image sur click, en fonction de si 'lon charge tout instant ou si l'on faire un changement progressif
};

template<typename nameClass, typename returnType>
void Button::actionOnClick(returnType (nameClass::*ptr)(), nameClass & object) const
{
    if(m_isPressed)
        (object.*ptr)();
}

template<typename nameClass, typename returnType, typename arg>
void Button::actionOnClick(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct) const
{
    if(m_isPressed)
        (object.*ptr)(argumentPtrFct);
}


template<typename nameClass, typename returnType>
void Button::eventButton(returnType (nameClass::*ptr)(), nameClass & object, const SDL_Event &event)
{
    curseurIsHover(event);
    isClick(event);
    if(m_isHover){

    }
    if(m_isPressed)
    {
        actionOnClick(ptr, object);
    }
    m_isPressed = false;
}

template<typename nameClass, typename returnType, typename arg>
void Button::eventButton(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct ,const SDL_Event &event)
{
    curseurIsHover(event);
    isClick(event);
    if(m_isHover){

    }
    if(m_isPressed)
    {
        actionOnClick(ptr, object, argumentPtrFct);
    }
    m_isHover = false;
    m_isPressed = false;
}


#endif // BUTTON_H
