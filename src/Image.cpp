#include "Image.h"
#include <SDL2/SDL_image.h>
#include <cassert>
#include <iostream>


void Image::loadImage(SDL_Renderer *rendu)
{
    m_psurface = IMG_Load(m_image.c_str());
    assert(m_psurface != nullptr && "Erreur de chemin (probablement)");
    m_ptexture = SDL_CreateTextureFromSurface(rendu, m_psurface);
    assert(m_ptexture != nullptr);
}

void Image::setDestination()
{
    if(m_destination != nullptr)
    {
        m_SDL_destination.x = m_destination->m_position.x;
        m_SDL_destination.y = m_destination->m_position.y;
        m_SDL_destination.w = m_destination->m_dimension.x;
        m_SDL_destination.h = m_destination->m_dimension.y;
    }
    else
    {
        std::cout<<"m_destination is null"<<std::endl;
        m_SDL_destination.x = 0;
        m_SDL_destination.y = 0;
        m_SDL_destination.w = 0;
        m_SDL_destination.h = 0;
    }
}

void Image::setSource()
{
    m_SDL_source.x = m_source.m_position.x;
    m_SDL_source.y = m_source.m_position.y;
    m_SDL_source.w = m_source.m_dimension.x;
    m_SDL_source.h = m_source.m_dimension.y;
}

Image::Image() : m_source(0, 0, 0, 0)
{
    m_image = "";
    m_destination = nullptr;
    m_psurface = nullptr;
    m_ptexture = nullptr;
    setSource();
    setDestination();
}

Image::Image(const std::string & cheminImage,Rectangle* destination,
             const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu)
    : m_source(0, 0, 0, 0), m_destination(destination)
{
    m_image = cheminImage;
    loadImage(rendu);
    m_source.m_dimension.x = m_psurface->w;
    m_source.m_dimension.y = m_psurface->h;
    setSource();
    setDestination();

    testInOut(dimFenetre);
    SDL_FreeSurface(m_psurface);
    m_psurface = nullptr;
}

Image::Image(const std::string & cheminImage, const Rectangle & source,
             Rectangle* destination, const Vec2<unsigned int> & dimFenetre,
             SDL_Renderer *rendu)
{
    m_image = cheminImage;
    m_source = source;
    m_destination = destination;
    setSource();
    setDestination();
    loadImage(rendu);
    SDL_FreeSurface(m_psurface);
    testInOut(dimFenetre);
}

void Image::testInOut(const Vec2<unsigned int> &dimFenetre)
{
    if(m_destination->m_position.y + m_destination->m_dimension.y > dimFenetre.y)
    {
        m_destination->m_position.y = dimFenetre.y - m_destination->m_dimension.y;
    }

    if(m_destination->m_position.x + m_destination->m_dimension.x > dimFenetre.x)
    {
        m_destination->m_position.x = dimFenetre.x - m_destination->m_dimension.x;
    }

    if(m_destination->m_position.x < 0)
    {
        m_destination->m_position.x = 0;
    }

    if(m_destination->m_position.y < 0)
    {
        m_destination->m_position.y = 0;
    }
}

void Image::display(SDL_Renderer* rendu)
{
    setDestination();
    SDL_RenderCopy(rendu, m_ptexture, &m_SDL_source, &m_SDL_destination);
}


Image::~Image()
{
    SDL_DestroyTexture(m_ptexture);
    m_ptexture = nullptr;
}

