#include "Instance.h"
#include <iostream>

Instance::Instance(SDL_Renderer *renderer) : m_rectInstance(500, 500, 500, 500), m_rectDoorOutInstance(20, 0, 30, 70), m_rectDoorInInstance(300, 0, 30, 70)
{
	if (renderer == NULL)
	{
		std::cerr << "Erreur dans le constructeur d'Instance, renderer est NULL" << std::endl;
		SDL_Quit();
		exit(1);
	}
	Vec2<unsigned int> windowDimensions = {WIDTH, HEIGHT};

	m_instanceMap[0] = new Image("../data/images/house.png", m_rectInstance, windowDimensions, renderer);
	m_instanceMap[1] = new Image("../data/images/door.png", m_rectDoorInInstance, windowDimensions, renderer);
	m_instanceMap[2] = new Image("../data/images/door.png", m_rectDoorOutInstance, windowDimensions, renderer);

	m_chargeInterieur = false;
	m_rectDoorInInstance = Rectangle(20, 0, 30, 70);
}

Instance::Instance(const std::string &pathImageInstance, const std::string &pathImageDoor, const Rectangle &rectInstance, const Rectangle &rectDoorOutInstance, SDL_Renderer *renderer)
{
	if (renderer == NULL)
	{
		std::cerr << "Erreur dans le constructeur d'Instance, renderer est NULL" << std::endl;
		SDL_Quit();
		exit(1);
	}

	m_rectInstance = rectInstance;
	std::cout << "position de l'instance : " << m_rectInstance.rectangle.x << ", " << m_rectInstance.rectangle.y << std::endl;
	m_rectDoorOutInstance = rectDoorOutInstance;

	SDL_Rect SDL_rectDoorOutInstance = rectDoorOutInstance.rectangle;
	std::cout << "position de rectDoorOutInstance : " << SDL_rectDoorOutInstance.x << ", " << SDL_rectDoorOutInstance.y << std::endl;
	std::cout << "dimensions de rectDoorOutInstance  : " << SDL_rectDoorOutInstance.w << ", " << SDL_rectDoorOutInstance.h << std::endl; 
	//la porte intérieur a les mêmes dimensions que la porte extérieur, mais elle est place est bas de l'écran
	m_rectDoorInInstance = Rectangle(WIDTH/2 - SDL_rectDoorOutInstance.w, HEIGHT - m_rectDoorOutInstance.rectangle.h, 
		SDL_rectDoorOutInstance.w, SDL_rectDoorOutInstance.h);

	Vec2<unsigned int> windowDimensions = {WIDTH, HEIGHT};
	//remplissage des 3 images
	//std::cout << "dimensions de l'instance : " << m_rectInstance.rectangle.w << ", " << m_rectInstance.rectangle.h << std::endl;
	m_instanceMap[0] = new Image(pathImageInstance, m_rectInstance, windowDimensions, renderer); //image de l'instance
	m_instanceMap[1] = new Image(pathImageDoor, m_rectDoorInInstance, windowDimensions, renderer); //porte d'entrée
	m_instanceMap[2] = new Image(pathImageDoor, m_rectDoorOutInstance, windowDimensions, renderer); //porte de sortie

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
	for (int i = 0; i < 3; i++)
	{
		delete m_instanceMap[i];
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
		//std::cout << "charge interieur" << std::endl;
		SDL_Rect rectangleFill = {0, 0, WIDTH, HEIGHT};
		SDL_RenderFillRect(renderer, &rectangleFill);

		//affichage de la porte de sortie
		m_instanceMap[1]->display(renderer);

		//affiche des ennemis
		for (long unsigned int i = 0; i < m_ennemis.size(); i++)
		{
			m_ennemis[i]->display(renderer);
			m_ennemis[i]->setLoaded(true);
		}
	}
	else
	{
		//affichage de l' instance
		m_instanceMap[0]->display(renderer);

		//affichage de la porte d'entrée
		m_instanceMap[2]->display(renderer);

		for (long unsigned int i = 0; i< m_ennemis.size(); i++)
		{
			m_ennemis[i]->setLoaded(false);
		}
	}
}

void Instance::TestPlayerTakeDoor(Character &character)
{
	Rectangle rectCharacter = character.getPos();

	//COLLISIONS
	if (!m_chargeInterieur)
	{
		//std::cout << "collision entre le joueur et la maison" << std::endl;

		//bord gauche du toit
		if (rectCharacter.in(Rectangle(m_rectInstance.rectangle.x, m_rectInstance.rectangle.y, 5, m_rectInstance.rectangle.h/2)))
		{
			character.move({-1, 0});
		}

		//bord droit du toit
		if (rectCharacter.in(Rectangle(m_rectInstance.rectangle.x + m_rectInstance.rectangle.w - 20, m_rectInstance.rectangle.y + 30, 5, 40)))
		{
			std::cout << "collision avec le bord droit du toit" << std::endl;
			character.move({1, 0});
		}

		//haut du toit
		if (rectCharacter.in(Rectangle(m_rectInstance.rectangle.x, m_rectInstance.rectangle.y + 30, 150, 10)))
		{
			std::cout << "collision avec le haut du toit" << std::endl;
			character.move({0, -1});
		}

		//bas du toit
		if (rectCharacter.in(Rectangle(m_rectInstance.rectangle.x, m_rectInstance.rectangle.y + 70, m_rectInstance.rectangle.w, 40)))
		{
			std::cout << "collision avec le bas du toit" << std::endl;
			character.move({0, 1});

		}
	}
	

	//extérieur -> intérieur
	if (rectCharacter.in(m_rectDoorOutInstance) && !m_chargeInterieur)
	{
		std::cout << "position du joueur : " << rectCharacter.rectangle.x << ", " << rectCharacter.rectangle.y << std::endl;
		std::cout << "passage de l'extérieur à l'intérieur" << std::endl;
		
		m_chargeInterieur = true;
		character.setPos(Rectangle(m_rectDoorInInstance.rectangle.x, m_rectDoorInInstance.rectangle.y - 50, rectCharacter.rectangle.w, rectCharacter.rectangle.h));
	}

	//si le joueur quitte sort par la porte de l'instance
	if (m_chargeInterieur && rectCharacter.in(m_rectDoorInInstance))
	{

		std::cout << "position du joueur : " << rectCharacter.rectangle.x << ", " << rectCharacter.rectangle.y << std::endl;
		std::cout << "passage de l'intérieur à l'extérieur" << std::endl;

		m_chargeInterieur = false;
		character.setPos(Rectangle(m_rectDoorOutInstance.rectangle.x - rectCharacter.rectangle.w, m_rectDoorOutInstance.rectangle.y, rectCharacter.rectangle.w, rectCharacter.rectangle.h));
	}
}