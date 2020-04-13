#include "Image.h"
#include <SDL2/SDL_image.h>
#include <cassert>
#include <iostream>


void Image::loadImage(SDL_Renderer *rendu)
{
    m_psurface = IMG_Load(m_image.c_str());
    assert(m_psurface != nullptr);
    m_ptexture = SDL_CreateTextureFromSurface(rendu, m_psurface);
    assert(m_ptexture != nullptr);
}

Image::Image() : m_source(0, 0, 0, 0), m_destination(0, 0, 0, 0)
{
    m_image = "";
    m_psurface = nullptr;
    m_ptexture = nullptr;
}

Image::Image(const std::string & cheminImage, SDL_Renderer *rendu)
{
    m_image = cheminImage;
    loadImage(rendu);

    setSource(Rectangle(0, 0, m_psurface->w, m_psurface->h));
    setDestination(m_source);

    SDL_FreeSurface(m_psurface);
    m_psurface = nullptr;
}

Image::Image(const std::string & cheminImage, const Rectangle & destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu)
{
    m_image = cheminImage;
    loadImage(rendu);
    setSource(Rectangle(0, 0, m_psurface->w, m_psurface->h));
    setDestination(m_source);
    testInOut(dimFenetre);
    SDL_FreeSurface(m_psurface);
    m_psurface = nullptr;
}

Image::Image(const std::string & cheminImage, const Rectangle & source, const Rectangle & destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu)
{
    m_image = cheminImage;
    loadImage(rendu);
    setSource(destination);
    setDestination(m_source);
    testInOut(dimFenetre);
}

void Image::testInOut(const Vec2<unsigned int> &dimFenetre)
{
    if(m_destination.m_position.y + m_destination.m_dimension.y > dimFenetre.y)
    {
        m_destination.m_position.y = dimFenetre.y - m_destination.m_dimension.y;
    }

    if(m_destination.m_position.x + m_destination.m_dimension.x > dimFenetre.x)
    {
        m_destination.m_position.x = dimFenetre.x - m_destination.m_dimension.x;
    }

    if(m_destination.m_position.x < 0)
    {
        m_destination.m_position.x = 0;
    }

    if(m_destination.m_position.y < 0)
    {
        m_destination.m_position.y = 0;
    }
}

void Image::move(const Rectangle &pos, const Vec2<unsigned int> & dimFenetre)
{
    m_destination = pos;
    testInOut(dimFenetre);
}

void Image::moveRight(const Vec2<unsigned int> & dimFenetre)
{
    m_destination.m_position.x ++;
    setDestination(m_destination);
    testInOut(dimFenetre);
}

void Image::moveLeft(const Vec2<unsigned int> & dimFenetre)
{
    m_destination.m_position.x --;
    setDestination(m_destination);
    testInOut(dimFenetre);
}

void Image::moveTop(const Vec2<unsigned int> &dimFenetre)
{
    m_destination.m_position.y --;
    setDestination(m_destination);
    testInOut(dimFenetre);
}

void Image::moveBottom(const Vec2<unsigned int> &dimFenetre)
{
    m_destination.m_position.y ++;
    setDestination(m_destination);
    testInOut(dimFenetre);
}

void Image::rotate(SDL_RendererFlip flip, float angle, const Vec2<int> & centre, SDL_Renderer* rendu)
{
    SDL_Point temp = {centre.x, centre.y};
    SDL_RenderClear(rendu);
    SDL_RenderCopyEx(rendu, m_ptexture, &m_SDL_source, &m_SDL_destination, angle, &temp, flip);
    SDL_RenderPresent(rendu);
}

void Image::display(SDL_Renderer* rendu)
{
    std::cout<<m_SDL_source.w<< " "<<m_source.m_dimension.x<<std::endl;
    SDL_RenderCopy(rendu, m_ptexture, &m_SDL_source, &m_SDL_destination);
}

void Image::setDestination(const Rectangle &r)
{
    m_destination = r;
    m_SDL_destination.x = r.m_position.x;
    m_SDL_destination.y = r.m_position.y;
    m_SDL_destination.w = r.m_dimension.x;
    m_SDL_destination.h = r.m_dimension.y;
}

void Image::setSource(const Rectangle &r)
{
    m_source = r;
    m_SDL_source.x = r.m_position.x;
    m_SDL_source.y = r.m_position.y;
    m_SDL_source.w = r.m_dimension.x;
    m_SDL_source.h = r.m_dimension.y;
}

Image::~Image()
{
    SDL_DestroyTexture(m_ptexture);
    m_ptexture = nullptr;
}

