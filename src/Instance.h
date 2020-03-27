#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "Rectangle.h"
#include "Image.h"

/**
 * @brief     La classe Instance représente une maison ou un dongeon
 */
class Instance
{
	public:
		/**
		 * @brief      Construit une nouvelle instance
		 *
		 * @param      renderer  Le rendu
		 */
		Instance(SDL_Renderer *renderer);

		/**
		 * @brief      Construit une nouvelle instance
		 *
		 * @param[in]  position  position sur l'écran
		 * @param[in]  door      position de la porte sur l'écran
		 * @param      renderer  Le rendu
		 */
		Instance(const Rectangle &position, const Rectangle &door, SDL_Renderer *renderer);

		/**
		 * @brief      Détruit l'objet.
		 * 
		 * Désalloue la mémire pour les images
		 */
		~Instance();

		/**
		 * @brief      Accesseur de m_door
		 *
		 * @return     Le rectangle m_door
		 */
		Rectangle getDoor() const { return m_door; }

		/**
		 * @brief      Accesseur de m_position
		 *
		 * @return     Le rectangle m_position
		 */
		Rectangle getPos() const { return m_position; }

		/**
		 * @brief      Affiche l'instance
		 *
		 * @param      renderer  Le rendu
		 */
		void display(SDL_Renderer *renderer);

	
	private:
		Rectangle m_position;
		Rectangle m_door;
		std::vector<Image*> m_instanceMap;

		
};

#endif