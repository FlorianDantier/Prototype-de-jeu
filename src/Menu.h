#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <string>

class Menu
{
private:
    unsigned int m_nbChoices;
    Rectangle m_position;
    Button* m_choices;
    bool m_isLoad;
    bool m_isOpen;
    Button* m_openButton;
    Button* m_closeButton; // Cette ligne modifié .... A finir ...


    void open(const Vec2<int> & leftClick);
    void close(const Vec2<int> & leftClick);
    void isLoadButton();

public:
    Menu& operator=(const Menu &copie);

    //===============CONSTRUCTEURS===============
    Menu();
    Menu(unsigned int nbButton, bool isOpen , bool isLoad, const Button &open, const Button &close);
    //==============FIN CONSTRUCTEURS==============

    //===============ACCESSEURS===============
    bool getIsLoad() const;
    void setIsLoad(const bool isLoad);

    Button& getChoice(const unsigned int indice) const;
    void setChoice(const Button & btn, const unsigned int indice);

    Button& getOpenButton() const;
    void setOpenButton(const Button & b);

    Button& getCloseButton() const;
    void setCloseButton(const Button & b);

    bool getIsOpen() const;
    void setIsOpen(const bool isOpen);
    //===============FIN ACCESSEURS===============

    //=================EVENEMENT==================
    void mouseLeftClick(const Vec2<int> &leftClick);
    //===============FIN EVENEMENT===============
    //void display(SDL_Renderer* renderer);

    Button& listenEvent(const unsigned int indice);

    ~Menu();
};

#endif // MENU_H
