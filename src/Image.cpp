#include "Image.h"
#include <SDL2/SDL_image.h>
#include <cassert>
#include <iostream>


void Image::loadImage(const std::string &cheminImage, SDL_Renderer *rendu)
{
    m_psurface = IMG_Load(cheminImage.c_str());
    std::string errorMessage = "Erreur lors du chargement de l'image : " + cheminImage;
    assert(m_psurface != nullptr && errorMessage.c_str());

    errorMessage.clear();
    errorMessage = "Erreur lors de la création de la texture pour l'image : " + cheminImage;
    m_ptexture = SDL_CreateTextureFromSurface(rendu, m_psurface);
    assert(m_ptexture != nullptr && errorMessage.c_str());
}

Image::Image() : m_source(0, 0, 0, 0), m_destination(0, 0, 0, 0)
{
    // Chemin fichier
    m_psurface = nullptr;
    m_ptexture = nullptr;
}

Image::Image(const std::string & cheminImage, SDL_Renderer *rendu)
{
    loadImage(cheminImage, rendu);

    m_source = Rectangle(0, 0, m_psurface->w, m_psurface->h); // À confirmer ...
    m_destination = m_source;

    SDL_FreeSurface(m_psurface);
    m_psurface = nullptr;
}

Image::Image(const std::string & cheminImage, const Rectangle & destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu)
{
    loadImage(cheminImage, rendu);
    m_source = Rectangle(0, 0, m_psurface->w, m_psurface->h);
    m_destination = destination;
    testInOut(dimFenetre);
    SDL_FreeSurface(m_psurface);
    m_psurface = nullptr;
}

Image::Image(const std::string & cheminImage, const Rectangle & source, const Rectangle & destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu)
{
    loadImage(cheminImage, rendu);
    m_source = source;
    m_destination = destination;
    testInOut(dimFenetre);
}

void Image::testInOut(const Vec2<unsigned int> &dimFenetre)
{
    if(m_destination.rectangle.y + m_destination.rectangle.h > dimFenetre.y)
    {
        m_destination.rectangle.y = dimFenetre.y - m_destination.rectangle.h;
    }

    if(m_destination.rectangle.x + m_destination.rectangle.w > dimFenetre.x)
    {
        m_destination.rectangle.x = dimFenetre.x - m_destination.rectangle.w;
    }

    if(m_destination.rectangle.x < 0)
    {
        m_destination.rectangle.x = 0;
    }

    if(m_destination.rectangle.y < 0)
    {
        m_destination.rectangle.y = 0;
    }
}

void Image::move(const Rectangle &pos, const Vec2<unsigned int> & dimFenetre)
{
    m_destination = pos;
    testInOut(dimFenetre);
}

void Image::moveRight(const Vec2<unsigned int> & dimFenetre)
{
    m_destination.rectangle.x ++;
    testInOut(dimFenetre);
}

void Image::moveLeft(const Vec2<unsigned int> & dimFenetre)
{
    m_destination.rectangle.x --;
    testInOut(dimFenetre);
}

void Image::moveTop(const Vec2<unsigned int> &dimFenetre)
{
    m_destination.rectangle.y --;
    testInOut(dimFenetre);
}

void Image::moveBottom(const Vec2<unsigned int> &dimFenetre)
{
    m_destination.rectangle.y ++;
    testInOut(dimFenetre);
}

void Image::rotate(SDL_RendererFlip flip, float angle, const Vec2<int> & centre, SDL_Renderer* rendu)
{
    SDL_Point temp = {centre.x, centre.y};
    SDL_RenderClear(rendu);
    SDL_RenderCopyEx(rendu, m_ptexture, &m_source.rectangle, &m_destination.rectangle, angle, &temp, flip);
    SDL_RenderPresent(rendu);
}

void Image::display(SDL_Renderer* rendu) // N'éfface pas tout ?
{
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, m_ptexture, &m_source.rectangle, &m_destination.rectangle);
    SDL_RenderPresent(rendu);
}

Image::~Image()
{
    SDL_DestroyTexture(m_ptexture);
    m_ptexture = nullptr;
}

