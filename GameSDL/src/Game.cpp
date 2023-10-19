#include "Game.h"

// ----- TO BE REMOVED -------
const float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

GLuint basic_shader_program;

unsigned int VBO;
unsigned int VAO;

// ---------------------------

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
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	}
	else 
	{
		flags = SDL_WINDOW_OPENGL;
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

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		glContext = SDL_GL_CreateContext(window);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			printf("Failed to initialize OpenGL context\n");
			isRunning = false;
		}
		glEnable(GL_DEPTH_TEST);
		glInfo();
		initBasicProgram();
	}
}

void Game::Event()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) 
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{

}

void Game::Render()
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(basic_shader_program);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
	//SDL_RenderPresent(renderer);
}

void Game::glInfo()
{
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
}

void Game::initBasicProgram()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	basic_shader_program = Common::createShader("res/shaders/basic.vert", "res/shaders/basic.frag");
	glUseProgram(basic_shader_program);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Game::Quit()
{
	std::cout << "Quit Game" << std::endl;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
