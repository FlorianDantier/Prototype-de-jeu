#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

/**
 * @brief      Cette classe décrit une instance de Jeu
 */

class Game
{
	public:
		/**
		 * @brief      Construit une nouvelle instance de Jeu
		 */
		Game();
		/**
		 * @brief      Détruit l'objet
		 */
		~Game();
		/**
		 * @brief      Boucle qui comprend toute les mises à jour dans le jeu
		 */
		void MainLoop();

	private:

		SDL_Window *window;
		
		SDL_Renderer *renderer;
	
};

#endif