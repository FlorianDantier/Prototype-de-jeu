#ifndef BUTTON_H
#define BUTTON_H

#include "Rectangle.h"
#include <string>
#include <iostream>


/**
 * @brief      This class describes a button.
 * 
 * A button has its own state and is composed of a rectangle.
 * 
 * Example of usage:
 * 
 * @code
 * //creation of a button
 * Button RunButton(Rectangle(100, 150, 30, 70), false);
 * 
 * //copy a button
 * Button OptionButton = RunButton;
 * 
 * @endcode
 */
class Button
{
private:
    Rectangle* m_position;
    bool m_isLoad;
    template<typename nameClass, typename returnType>
    void actionOnClick(returnType (nameClass::*ptr)(), nameClass & object);

    template<typename nameClass, typename returnType, typename arg>
    void actionOnClick(returnType (nameClass::*ptr)(arg*), nameClass & object,
                       arg* argumentPtrFct);

    template<typename nameClass, typename returnType, typename arg>
    void actionOnClick(returnType (nameClass::*ptr)(arg), nameClass & object,
                       const arg & argumentPtrFct);

public:
    /**
     * @brief      Constructs a new instance of button
     * 
     * The default constructor
     */
    Button();

    /**
     * @brief      Constructs a new instance of button
     *
     * @param[in]  position  The rectangle who represent
     * @param[in]  isLoad    Indicates if it has been load
     */
    Button(const Rectangle & position, bool isLoad);

    /**
     * @brief      Constructs a new instance of button
     * 
     * The constructor by copy
     *
     * @param[in]  copie  A constant reference of the button to be copied
     */
    Button(const Button &copie);

    /**
     * @brief      Destroys the object.
     */
    ~Button();

    /**
     * @brief      Assignment operator.
     *
     * @param[in]  copie  The button to be copied
     *
     * @return     The result of the assignment is a reference to the button
     */
    Button& operator=(const Button &copie);

    /**
     * @brief      Gets the rectangle of this button
     *
     * @return     The rectangle
     */
    Rectangle &getPosition() const;

    /**
     * @brief      Sets the this button is load (true) or not (false)
     *
     * @param[in]  b     A boolean
     */
    void setIsLoad(const bool b);

    /**
     * @brief      True is the Menu is load, otherwise it returns false
     *
     * @return     A boolean
     */
    bool getIsLoad() const;

    /**
     * @brief      Determines whether the specified mouse position is pressed.
     *
     * @param[in]  mousePos  The mouse position
     *
     * @return     True if the specified mouse position is pressed, False otherwise.
     */
    bool isPressed(const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType>
    void eventButton(returnType (nameClass::*ptr)(), nameClass & object,
                     const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType, typename arg>
    void eventButton(returnType (nameClass::*ptr)(arg), nameClass & object,
                     const arg & argumentPtrFct , const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType, typename arg>
    void eventButton(returnType (nameClass::*ptr)(arg*), nameClass & object,
                     arg* argumentPtrFct , const Vec2<int> &mousePos);
};

template<typename nameClass, typename returnType>
void Button::actionOnClick(returnType (nameClass::*ptr)(), nameClass & object)
{
    if(m_isLoad)
        (object.*ptr)();
}

template<typename nameClass, typename returnType, typename arg>
void Button::actionOnClick(returnType (nameClass::*ptr)(arg*),
                           nameClass & object, arg* argumentPtrFct)
{
     if(m_isLoad)
        (object.*ptr)(argumentPtrFct);
}

template<typename nameClass, typename returnType, typename arg>
void Button::actionOnClick(returnType (nameClass::*ptr)(arg),
                           nameClass & object, const arg & argumentPtrFct)
{
    if(m_isLoad)
        (object.*ptr)(argumentPtrFct);
}

template<typename nameClass, typename returnType>
void Button::eventButton(returnType (nameClass::*ptr)(), nameClass & object,
                         const Vec2<int> &mousePos)
{
    if(isPressed(mousePos))
    {
        actionOnClick(ptr, object);
    }
}


template<typename nameClass, typename returnType, typename arg>
void Button::eventButton(returnType (nameClass::*ptr)(arg), nameClass & object,
                         const arg & argumentPtrFct , const Vec2<int> &mousePos)
{
    if(isPressed(mousePos))
    {
        actionOnClick(ptr, object, argumentPtrFct);
    }
}


template<typename nameClass, typename returnType, typename arg>
void Button::eventButton(returnType (nameClass::*ptr)(arg*), nameClass & object,
                         arg* argumentPtrFct, const Vec2<int> &mousePos)
{
    if(isPressed(mousePos))
    {
        actionOnClick(ptr, object, argumentPtrFct);
    }
}


#endif // BUTTON_H
