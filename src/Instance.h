#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "Rectangle.h"
#include "Image.h"
#include "Character.h"
#include "Player.h"

/**
 * @brief     La classe Instance représente une maison ou un dongeon
 */
class Instance
{
	public:
		//créé une nouvelle instance (maison ou dongeon)
		Instance(SDL_Renderer *renderer);
		//crée une nouvelle instance de dongeon
		Instance(const Rectangle &position, const Rectangle &door, Vec2<unsigned int> winDim, SDL_Renderer *renderer);
		//détruit l'instance
		~Instance();
		//test si le joueur passe la porte
		void TestPlayerTakeDoor(Player &p);
		//retourne le rectangle représentant la porte
		Rectangle getDoor() const { return m_door; }
		//retourne le rectangle représentant l'instance
		Rectangle getPos() const { return m_position; }
		//procédure d'affichage de l'instance
		void display(SDL_Renderer *renderer);

	
	private:
		//gère les collisions entre le joueur et l'instance
		bool isCollision(Player &p);
		//void charge(const Map &map, SDL_Renderer *renderer);

		std::vector<Character*> m_ennemis;

		Rectangle m_position;
		Rectangle m_door;
		Rectangle m_doorInInstance;
		std::vector<Image*> m_instanceMap;
		bool m_chargeInterieur;

		
};

#endif