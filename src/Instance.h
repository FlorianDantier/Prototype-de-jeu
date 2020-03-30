#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>
#include "Rectangle.h"
#include "Image.h"
#include "Character.h"

class Player
{
public:
	Player(const Image &im)
	{
		m_position = {200, 140};
		m_imcharacter = im;
	}

	void moove(int direction)
	{
		Rectangle pos;
		//up
		if (direction == 0)
		{
			m_position.y -= 3;
		}

		//bas
		if (direction == 1)
		{
			m_position.y += 3;
		}

		//gauche
		if (direction == 2)
		{
			m_position.x -= 3;
		}

		//droite
		if (direction == 3)
		{
			m_position.x += 3;
		}

		pos = Rectangle(m_position.x, m_position.y, 50, 50);
		m_imcharacter.move(pos, {640, 480});
	}

	Rectangle getPos() { return Rectangle(m_position.x, m_position.y, 30, 50); }

	void setPos(const Rectangle &position)
	{
		m_imcharacter.move(position, {640, 480});
	}

	void display(SDL_Renderer *renderer)
	{
		m_imcharacter.display(renderer);
	}

private:
	Vec2<int> m_position;
	Image m_imcharacter;
};

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
		//void charge(const Map &map, SDL_Renderer *renderer);

		std::vector<Character*> m_ennemis;

		Rectangle m_position;
		Rectangle m_door;
		Rectangle m_doorInInstance;
		std::vector<Image*> m_instanceMap;
		bool m_chargeInterieur;

		
};

#endif