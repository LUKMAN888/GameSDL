#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	isRunning = true;

	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		window = SDL_CreateWindowWithPosition(title, x, y, width, height, flags);
		if (!window) 
		{
			std::cout << "Window failed to be created" << std::endl;
			isRunning = false;
			return;
		}
		renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!renderer)
		{
			std::cout << "Renderer failed to be created" << std::endl;
			isRunning = false;
			return;
		}
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
}

void Game::Event()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_EVENT_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::Update()
{

}

void Game::Render()
{
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Quit()
{
	std::cout << "Quit Game" << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
