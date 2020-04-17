#ifndef BUTTON_H
#define BUTTON_H

#include "Rectangle.h"
#include <string>
#include <iostream>
/**
 * @brief Cette classe permet de créer un bouton
 */


class Button
{
private:
    Rectangle* m_position;
    bool m_isLoad;
    template<typename nameClass, typename returnType>
    void actionOnClick(returnType (nameClass::*ptr)(), nameClass & object);

    template<typename nameClass, typename returnType, typename arg>
    void actionOnClick(returnType (nameClass::*ptr)(arg*), nameClass & object, arg* argumentPtrFct);

    template<typename nameClass, typename returnType, typename arg>
    void actionOnClick(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct);

public:
    Button();
    Button(const Rectangle & position, bool isLoad);
    Button(const Button &copie);
    ~Button();

    Button& operator=(const Button &copie);

    Rectangle &getPosition() const;

    void setIsLoad(const bool b);
    bool getIsLoad() const;

    bool isPressed(const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType>
    void eventButton(returnType (nameClass::*ptr)(), nameClass & object, const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType, typename arg>
    void eventButton(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct , const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType, typename arg>
    void eventButton(returnType (nameClass::*ptr)(arg*), nameClass & object,arg* argumentPtrFct , const Vec2<int> &mousePos);
};

template<typename nameClass, typename returnType>
void Button::actionOnClick(returnType (nameClass::*ptr)(), nameClass & object)
{
    if(m_isLoad)
        (object.*ptr)();
}

template<typename nameClass, typename returnType, typename arg>
void Button::actionOnClick(returnType (nameClass::*ptr)(arg*), nameClass & object, arg* argumentPtrFct)
{
     if(m_isLoad)
        (object.*ptr)(argumentPtrFct);
}

template<typename nameClass, typename returnType, typename arg>
void Button::actionOnClick(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct)
{
    if(m_isLoad)
        (object.*ptr)(argumentPtrFct);
}

template<typename nameClass, typename returnType>
void Button::eventButton(returnType (nameClass::*ptr)(), nameClass & object, const Vec2<int> &mousePos)
{
    if(isPressed(mousePos))
    {
        actionOnClick(ptr, object);
    }
}


template<typename nameClass, typename returnType, typename arg>
void Button::eventButton(returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct , const Vec2<int> &mousePos)
{
    if(isPressed(mousePos))
    {
        actionOnClick(ptr, object, argumentPtrFct);
    }
}


template<typename nameClass, typename returnType, typename arg>
void Button::eventButton(returnType (nameClass::*ptr)(arg*), nameClass & object,arg* argumentPtrFct, const Vec2<int> &mousePos)
{
    if(isPressed(mousePos))
    {
        actionOnClick(ptr, object, argumentPtrFct);
    }
}


#endif // BUTTON_H
