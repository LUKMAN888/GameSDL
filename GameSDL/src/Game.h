#pragma once

#include "SDL3/SDL.h"
#include <stdio.h>
#include <iostream>

class Game
{
	public:
		Game();
		~Game();

		void Init(const char* title, int x, int y, int width, int height, bool fullscreen);

		void Event();
		void Update();
		void Render();

		void Quit();

		bool running() { return isRunning; }

	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;

};

