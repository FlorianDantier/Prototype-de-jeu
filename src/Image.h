#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include "Rectangle.h"
#include <iostream>
//const std::string path = "/home/florian/Dropbox/Licence/L2/S4/LIFAP4/projet_lifap4/data/";
const std::string path = "/home/joris/Bureau/lifap4/projet_lifap4/data/";


class Image
{
private:
    void testInOut(const Vec2 <unsigned int> & dimFenetre);
    void loadImage(SDL_Renderer* rendu);

    void setDestination();
    void setSource();

    SDL_Surface* m_psurface;
    SDL_Texture* m_ptexture;
    SDL_Rect m_SDL_source;
    SDL_Rect m_SDL_destination;
    Rectangle m_source;
    Rectangle* m_destination;
    std::string m_image;


public:
    /*------CONSTRUCTEUR-------*/
    Image();
    Image(const std::string & cheminImage, Rectangle* destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu); // Ici on choisis les dimesion et la pos
    Image(const std::string & cheminImage, const Rectangle & source, Rectangle* destination , const Vec2<unsigned int> & dimFenetre, SDL_Renderer *rendu);

    void rotate(SDL_RendererFlip flip, float angle, const Vec2<int> & centre, SDL_Renderer* rendu);

    /*------ " DRAW " -------*/
    void display(SDL_Renderer* rendu);

    ~Image();
};

#endif // IMAGE_H
