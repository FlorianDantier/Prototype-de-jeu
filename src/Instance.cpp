#include "Instance.h"
#include <iostream>

Instance::Instance(SDL_Renderer *renderer) : m_position(500, 500, 500, 500), m_door(20, 0, 30, 70)
{
	Image *houseIm = new Image("../data/images/House.png", renderer);
	m_instanceMap.push_back(houseIm);
	m_chargeInterieur = false;
	m_doorInInstance = Rectangle(20, 0, 30, 70);
}

Instance::Instance(const Rectangle &position, const Rectangle &door, Vec2<unsigned int> winDim, SDL_Renderer *renderer)
{
	if (renderer == NULL)
	{
		std::cerr << "Erreur dans l'appel au constructeur d'Instance, renderer est NULL" << std::endl;
		SDL_Quit();
		exit(1);
	}
	m_position.rectangle = position.rectangle;
	m_door.rectangle = door.rectangle;
	//apparition dans l'instance en bas au centre de l'écran
	m_doorInInstance = Rectangle(300, 430, 40, 40);

	Image *houseIm = new Image("../data/images/House.png", position, winDim, renderer);
	Image *doorIm = new Image("../data/images/door.png", m_door, winDim, renderer);
	m_instanceMap.push_back(houseIm);
	m_instanceMap.push_back(doorIm);
	m_chargeInterieur = false;

	//ennemi (characters)
	Character *enemi;
	//4 clone du même enemi mais seront indépendant
	int EnnemisPositions[][2] = {
		{40, 150},
		{60, 50 },
		{160, 300}
	};

	for (int i = 0; i < 3; i++)
	{
		enemi = new Character(Rectangle(EnnemisPositions[i][0], EnnemisPositions[i][1], 40, 40), 100, "../data/Enemy.png", renderer, 10);
		m_ennemis.push_back(enemi);
	}
}

Instance::~Instance()
{
	for (auto i = m_instanceMap.begin(); i != m_instanceMap.end(); ++i)
	{
		Image *image = *i;
		delete image;
	}

	for (auto i = m_ennemis.begin(); i != m_ennemis.end(); ++i)
	{
		Character *enemi = *i;
		delete enemi;
	}
}

void Instance::display(SDL_Renderer *renderer)
{
	if (m_chargeInterieur)
	{
		//std::cout << "doit charger l'intérieur" << std::endl;
		//std::cout << "charge interieur" << std::endl;
		SDL_Rect rectangle = Rectangle(0, 0, 640, 480).rectangle;
		SDL_RenderFillRect(renderer, &rectangle);

		//affiche de la porte de sortie
		m_instanceMap[1]->display(renderer);
		//SDL_RenderFillRects(SDL_Renderer *renderer, const SDL_Rect *rects, int count)
		//affiche des ennemis
		for (long unsigned int i = 0; i < m_ennemis.size(); i++)
		{
			m_ennemis[i]->display(renderer);
			m_ennemis[i]->setLoaded(true);
		}
	}
	else
	{
		//affiche d'une instance l'extérieur + la porte
		m_instanceMap[0]->display(renderer);
		m_instanceMap[1]->display(renderer);

		for (long unsigned int i = 0; i< m_ennemis.size(); i++)
		{
			m_ennemis[i]->setLoaded(false);
		}
	}
}

void Instance::TestPlayerTakeDoor(Player &p)
{
	Rectangle rectPlayer = p.getPos();
	Rectangle TeleportPosition;
	if (rectPlayer.in(m_door) && !m_chargeInterieur)
	{
		std::cout << "position du joueur : " << rectPlayer.rectangle.x << ", " << rectPlayer.rectangle.y << std::endl;
		std::cout << "passe la porte de l'extérieur" << std::endl;
		
		m_instanceMap[1]->move(m_doorInInstance, {640, 480});

		TeleportPosition = Rectangle(m_doorInInstance.rectangle.x, m_doorInInstance.rectangle.y - 50, rectPlayer.rectangle.w, rectPlayer.rectangle.h);
		//téléportation du joueur vers une position proche de la porte intérieur de l'instance
		p.setPos(TeleportPosition);
		m_chargeInterieur = true;
	}

	//si le joueur quitte sort par la porte de l'instance
	if (m_chargeInterieur && rectPlayer.in(m_doorInInstance))
	{

		std::cout << "position du joueur : " << rectPlayer.rectangle.x << ", " << rectPlayer.rectangle.y << std::endl;
		std::cout << "passe la porte de l'intérieur" << std::endl;

		m_instanceMap[1]->move(m_door, {640, 480});
		
		
		TeleportPosition = Rectangle(m_door.rectangle.x, m_door.rectangle.y - 45, rectPlayer.rectangle.w, rectPlayer.rectangle.h);
		std::cout << "le personnage a été téléloporté de l'intérieur vers l'extérieur" << std::endl;
		p.setPos(TeleportPosition);

		m_chargeInterieur = false;
	}
}

