#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include <array>
#include "Rectangle.h"
#include "Image.h"
#include "Character.h"
#include "Def.h"

/**
 * @brief     La classe Instance représente une maison ou un dongeon
 */
class Instance
{
	public:
		//créé une nouvelle instance (maison ou dongeon)
		Instance(SDL_Renderer *renderer);
		//crée une nouvelle instance de dongeon
		Instance(const std::string &pathImageInstance, const std::string &pathImageDoor, const Rectangle &rectInstance, const Rectangle &rectDoor, SDL_Renderer *renderer);
		//détruit l'instance
		~Instance();
		//test si le joueur passe la porte
		void TestPlayerTakeDoor(Character &character);
		//retourne le rectangle représentant la porte en extérieur
		Rectangle getRectDoorOutInstance() const;
		//retourne le rectangle représentant la porte en intérieur
		Rectangle getRectDoorInInstance() const;
		//retourne le rectangle représentant l'instance en intégralité
		Rectangle getRectInstance() const;
		//procédure d'affichage de l'instance
		void display(SDL_Renderer *renderer);

	
	private:
		std::vector<Character*> m_ennemis;

		Rectangle m_rectInstance;
		Rectangle m_rectDoorOutInstance;
		Rectangle m_rectDoorInInstance;
		std::array<Image*, 4> m_instanceMap;
		bool m_chargeInterieur;

		
};

#endif