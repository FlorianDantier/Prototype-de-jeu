#include "Game.hpp"
#include <iostream>

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Erreur lors de l'intialisation du sous systeme video" << std::endl;

	}

	//création de la fenêtre de jeu
	window = SDL_CreateWindow("jeu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cerr << "Erreur dans la création de la fenêtre : " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	//création du rendu
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr)
	{
		std::cerr << "Erreur lors de la création du renderer : " << SDL_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	//Initialisation du chargement des images png avec SDL_Image 2
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cerr << "Erreur lors de l'initialisation de SDL_image : " << IMG_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() < 0)
	{
		std::cerr << "Erreur lors de l'initialisation de SDL_ttf : " << TTF_GetError() << std::endl;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	int flags = MIX_INIT_MP3;
	int initted = Mix_Init(flags);

	if ((initted & flags) != flags)
	{
		std::cerr << "Erreur dans l'initialisation de SDL_mixer : " << Mix_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	 /* Open 44.1KHz, signed 16bit, system byte order,
    stereo audio, using 1024 byte chunks (voir la doc pour plus d'infos) */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        std::cerr << "Mix_OpenAudio Error : " << Mix_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Game::MainLoop()
{
	bool stop = false;
	SDL_Event event;
	while (!stop)
	{
		//évènments
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				stop = true;
			}

			if (event.type == SDL_KEYUP)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						stop = true;
						break;
				}
			}
		}

		//set the render draw color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        //clear the current rendering target with the drawing color
        SDL_RenderClear(renderer);
        //update the screen with any rendering performed since the previous call.
        SDL_RenderPresent(renderer);
	}
}

//Destruction de la fenêtre et du rendu
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}