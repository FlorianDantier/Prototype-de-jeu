#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include "Rectangle.h"

class Image
{
private:
    void testInOut(const Vec2 <unsigned int> & dimFenetre);
    void loadImage(SDL_Renderer* rendu);

    void setDestination(const Rectangle & r);
    void setSource(const Rectangle & r);

    SDL_Surface* m_psurface;
    SDL_Texture* m_ptexture;
    Rectangle m_source;
    Rectangle m_destination;
    SDL_Rect m_SDL_source;
    SDL_Rect m_SDL_destination;
    std::string m_image;

public:
    /*------CONSTRUCTEUR-------*/
    Image();
    Image(const std::string & cheminImage, SDL_Renderer* rendu); // Les dimensions seront celle de l'image et la position sera en haut à gauche
    Image(const std::string & cheminImage, const Rectangle &destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu); // Ici on choisis les dimesion et la pos
    Image(const std::string & cheminImage, const Rectangle & source, const Rectangle & destination , const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu);


    /*------ " UPDATE " -------*/
    void move(const Rectangle &pos, const Vec2<unsigned int> & dimFenetre);
    void moveRight(const Vec2<unsigned int> & dimFenetre);
    void moveLeft(const Vec2<unsigned int> & dimFenetre);
    void moveTop(const Vec2<unsigned int> & dimFenetre);
    void moveBottom(const Vec2<unsigned int> & dimFenetre);
    void rotate(SDL_RendererFlip flip, float angle, const Vec2<int> & centre, SDL_Renderer* rendu);

    /*------ " DRAW " -------*/
    void display(SDL_Renderer* rendu);


    ~Image();
};

#endif // IMAGE_H
