#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "Rectangle.h"
#include "Image.h"

/**
 * @brief      This class describes an instance (House, Dungeon)
 */
class Instance
{
	public:
		/**
		 * @brief      Constructs a new instance.
		 */
		Instance(SDL_Renderer *renderer);

		/**
		 * @brief      Constructs a new instance.
		 *
		 * @param[in]  position  instance location in the screen
		 * @param[in]  door      door location in the the screen
		 */
		Instance(const Rectangle &position, const Rectangle &door, SDL_Renderer *renderer);

		/**
		 * @brief      Destroys the object.
		 * 
		 * Free the memory allocate for the images
		 */
		~Instance();

		/**
		 * @brief      Gets the door.
		 *
		 * @return     The door rectangle
		 */
		Rectangle getDoor() const { return m_door; }

		/**
		 * @brief      Gets the position.
		 *
		 * @return     The position rectangle
		 */
		Rectangle getPos() const { return m_position; }

		/**
		 * @brief      Displays the instance passing the renderer in parameter
		 *
		 * @param      renderer  The renderer
		 */
		void display(SDL_Renderer *renderer);

	
	private:
		Rectangle m_position;
		Rectangle m_door;
		std::vector<Image*> m_instanceMap;

		
};

#endif