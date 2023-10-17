#pragma once

#include "SDL3/SDL.h"
#include <glad/glad.h>
#include <stdio.h>
#include <iostream>

#include "Common.h"

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
		void glInfo();
		void initBasicProgram();

		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_GLContext glContext;

};

