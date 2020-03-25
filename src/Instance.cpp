#include "Instance.h"
#include <iostream>

Instance::Instance(SDL_Renderer *renderer) : m_position(500, 500, 500, 500), m_door(20, 0, 30, 70)
{
	Image *houseIm = new Image("../data/images/House.png", renderer);
	m_instanceMap.push_back(houseIm);
}

Instance::Instance(const Rectangle &position, const Rectangle &door, SDL_Renderer *renderer)
{
	if (renderer == NULL)
	{
		std::cerr << "Erreur dans l'appel au constructeur d'Instance, renderer est NULL" << std::endl;
		SDL_Quit();
		exit(1);
	}
	m_position.rectangle = position.rectangle;
	m_door.rectangle = door.rectangle;

	Vec2<unsigned int> winDim(1024, 768);
	Image *houseIm = new Image("../data/images/House.png", position, winDim, renderer);
	m_instanceMap.push_back(houseIm);

}

Instance::~Instance()
{
	for (auto im = m_instanceMap.begin(); im != m_instanceMap.end(); ++im)
	{
		Image *image = *im;
		delete image;
	}
}

void Instance::display(SDL_Renderer *renderer)
{
	m_instanceMap[0]->display(renderer);
}