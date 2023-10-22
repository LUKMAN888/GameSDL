#pragma once

#include "SDL3/SDL.h"
#include <glad/glad.h>

#include <stdio.h>
#include <iostream>
#include <map>
#include <glm.hpp>
#include <gtc/type_ptr.inl>

#include "Common.h"
#include "Camera.h"

class Game
{
	public:
		Game(const char* title, int x, int y, int width, int height, bool fullscreen);
		Game();
		~Game();

		void Init(const char* title, int x, int y, int width, int height, bool fullscreen);

		void Event();
		void Update();
		void Render();
		
		void Quit();

		bool Running() { return is_running; }

	private:
		void glInfo();
		void initBasicProgram();
		void initKeyboardState();
		void processKeyEvent(Uint8 key_state, bool key_down);
		void mouseMoveEvent(SDL_MouseMotionEvent event);

		std::map<Uint8, bool> keyboard_state;
		bool is_running;
		SDL_Window* window;
		SDL_GLContext gl_context;
		Camera camera;
};

