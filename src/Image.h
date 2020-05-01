#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <string>
#include "Rectangle.h"
#include <iostream>


/**
 * @brief      This class describes an image.
 * 
 * An image is a rectangle with a texture inside and it can be displayed on the screen.
 * 
 * Example of usage :
 * @code
 * ...
 * //load the warrior image
 * Image *warrior = new Image("../data/warrior.png", &Rectangle(150, 200, 50, 50), windowSize, renderer);
 * 
 * //display the warrior image
 * warrior->display(renderer);
 * @endcode
 */
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
    /*------CONSTRUCTOR-------*/
    /**
     * @brief      Constructs a new instance of Image
     * 
     */
    Image();

    /**
     * @brief      Constructs a new instance of Image
     *
     * @param[in]  cheminImage  the path of the image
     * @param      destination  a pointer to the destination rectangle
     * @param[in]  dimFenetre   window dimensions
     * @param      rendu        the renderer
     */
    Image(const std::string & cheminImage, Rectangle* destination, const Vec2<unsigned int> & dimFenetre, SDL_Renderer* rendu); // Ici on choisis les dimesion et la pos

    /**
     * @brief      Constructs a new instance of Image
     *
     * @param[in]  cheminImage  the path of the image
     * @param[in]  source       the source rectangle
     * @param      destination  a pointer to the destination rectangle
     * @param[in]  dimFenetre   window dimensions
     * @param      rendu        the renderer
     */
    Image(const std::string & cheminImage, const Rectangle & source, Rectangle* destination , const Vec2<unsigned int> & dimFenetre, SDL_Renderer *rendu);

    /**
     * @brief      Rotate the image
     *
     * @param[in]  flip    The flip
     * @param[in]  angle   The angle
     * @param[in]  centre  The rotation center
     * @param      rendu   The renderer
     */
    void rotate(SDL_RendererFlip flip, float angle, const Vec2<int> & centre, SDL_Renderer* rendu);

    /*------ " DRAW " -------*/
    /**
     * @brief      Displays the image
     *
     * @param      rendu the renderer
     */
    void display(SDL_Renderer* rendu);

    ~Image();
};

#endif // IMAGE_H
