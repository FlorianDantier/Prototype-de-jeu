#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <SDL2/SDL.h>
#include "Image.h"
#include <string>

class Menu
{
private:
    Button* m_choices;
    unsigned int m_nbChoices;
    Rectangle m_position;

    bool m_isOpen;
public:
    Button m_openButton;
    Button m_closeButton;
    Image m_background;

    Menu();
    Menu(int nbButton, const Rectangle &position, const std::string &pathImageBackground, SDL_Renderer *renderer, bool isOpen = false);
    void display(SDL_Renderer* renderer);
    void setChoice(const Button & btn, unsigned int indice);
    ~Menu();
};

#endif // MENU_H
