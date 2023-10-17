#pragma once
#include "SDL3/SDL.h"
#include <glad/glad.h>
#include <stdio.h>
#include <iostream>

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void Init();
		void render();

	private:
		static unsigned int CreateShader(const std::string& vertexPath, const std::string fragmentPath);
};

