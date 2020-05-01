#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "common.h"
#include <string>
#include <cassert>


/**
 * @brief      This class describes a menu.
 * 
 * A menu is composed of buttons.
 * 
 * Example of usage :
 * @code
 * //creation of a button
 * Button notLoad(Rectangle(-1 ,-1, -1, -1), false);
 * 
 * //creation of the menu
 * Menu *menu = new Menu(1, true, true, notLoad, notLoad);
 * 
 * //set the choice
 * menu->setChoice(Button (Rectangle  (50, 100, 550, 100), true), 0);
 * 
 * @endcode
 * 
 */
class Menu
{
protected:
    unsigned int m_nbChoices;
    Rectangle m_position;
    Button* m_choices;
    bool m_isLoad;
    bool m_isOpen;
    Button* m_openButton;
    Button* m_closeButton; // Cette ligne modifié .... A finir ...


    /**
     * @brief      Open the menu
     *
     * @param[in]  leftClick  The left click position
     */
    void open(const Vec2<int> & leftClick);

    /**
     * @brief      Close the menu
     *
     * @param[in]  leftClick  The left click position
     */
    void close(const Vec2<int> & leftClick);

    /**
     * @brief      Sets the close button and the open button as loaded or not
     */
    void isLoadButton();




public:
    /**
     * @brief      Assignment operator.
     *
     * @param[in]  copie  The menu to be copied
     *
     * @return     The result of the assignment
     */
    Menu& operator=(const Menu &copie);

    
    /**
     * @brief      Constructs a new instance of Menu
     */
    Menu();

    /**
     * @brief      Constructs a new instance of Menu
     *
     * @param[in]  nbButton  The number of buttons
     * @param[in]  isOpen    Indicates if it is open by default
     * @param[in]  isLoad    Indicates if it is load by default
     * @param[in]  open      The open button
     * @param[in]  close     The close button
     */
    Menu(unsigned int nbButton, bool isOpen , bool isLoad, const Button &open, const Button &close);
    

    /**
     * @brief      True is the Menu is load, otherwise it returns false
     *
     * @return     A boolean
     */
    bool getIsLoad() const;

    /**
     * @brief      Sets the Menu as loaded (true) or not(false)
     *
     * @param[in]  isLoad  Indicates if the menu is loaded or not
     */
    void setIsLoad(const bool isLoad);

    /**
     * @brief      Gets the choice.
     *
     * @param[in]  indice  The index of the choice represent by a button
     *
     * @return     A reference to the corresponding button
     */
    Button& getChoice(const unsigned int indice) const;

    /**
     * @brief      Sets the choice.
     *
     * @param[in]  btn     The new value of the button
     * @param[in]  indice  The index
     */
    void setChoice(const Button & btn, const unsigned int indice);

    /**
     * @brief      Gets a reference to the open button.
     *
     * @return     The open button.
     */
    Button& getOpenButton() const;

    /**
     * @brief      Sets the open button.
     *
     * @param[in]  b     a reference to the open button
     */
    void setOpenButton(const Button & b);

    /**
     * @brief      Gets a reference to the close button.
     *
     * @return     The close button.
     */
    Button& getCloseButton() const;

    /**
     * @brief      Sets the close button.
     *
     * @param[in]  b     a constant reference to the close button
     */
    void setCloseButton(const Button & b);

    /**
     * @brief      True if the Menu is open, otherwise it returns false
     *
     * @return     A boolean
     */
    bool getIsOpen() const;

    /**
     * @brief      Sets the menu as open(true) or not(false)
     *
     * @param[in]  isOpen  Indicates if the button is open or not
     */
    void setIsOpen(const bool isOpen);
    //===============FIN ACCESSEURS===============

    //=================EVENEMENT==================

    /**
     * @brief      Do a left click on the menu
     *
     * @param[in]  leftClick  The position of the left click
     */
    void mouseLeftClick(const Vec2<int> &leftClick);
    //===============FIN EVENEMENT===============
    //void display(SDL_Renderer* renderer);

    //Button& listenEvent(const unsigned int indice);

    
    template<typename nameClass, typename returnType>
    void listenEvent(const unsigned int indice, returnType (nameClass::*ptr)(), nameClass & object, const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType, typename arg>
    void listenEvent(const unsigned int indice, returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct , const Vec2<int> &mousePos);

    template<typename nameClass, typename returnType, typename arg>
    void listenEvent(const unsigned int indice, returnType (nameClass::*ptr)(arg*), nameClass & object,arg* argumentPtrFct , const Vec2<int> &mousePos);




    ~Menu();
};

template<typename nameClass, typename returnType>
void Menu::listenEvent(const unsigned int indice, returnType (nameClass::*ptr)(), nameClass & object, const Vec2<int> &mousePos)
{
    assert(indice >= 0 && indice < m_nbChoices);
    m_choices->eventButton(ptr, object, mousePos);
}

template<typename nameClass, typename returnType, typename arg>
void Menu::listenEvent(const unsigned int indice, returnType (nameClass::*ptr)(arg), nameClass & object, const arg & argumentPtrFct , const Vec2<int> &mousePos)
{
    assert(indice >= 0 && indice < m_nbChoices);
    m_choices[indice].eventButton(ptr, object, argumentPtrFct, mousePos);
}

template<typename nameClass, typename returnType, typename arg>
void Menu::listenEvent(const unsigned int indice, returnType (nameClass::*ptr)(arg*), nameClass & object,arg* argumentPtrFct , const Vec2<int> &mousePos)
{
    assert(indice >= 0 && indice < m_nbChoices);

    m_choices[indice].eventButton(ptr, object, argumentPtrFct, mousePos);
}

#endif // MENU_H
