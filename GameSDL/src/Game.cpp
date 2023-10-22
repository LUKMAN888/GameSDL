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


glm::mat4 projection_matrix;
glm::mat4 transformation_matrix = glm::mat4(1.0f);
const float NEAR = 0.1f;
const float FAR = 400.0f;

float lastX = 0, lastY = 0;
float posX = 0, posY = 0;
bool first_mouse = true;

// ---------------------------

Game::Game(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	Init(title, x, y, width, height, fullscreen);
}

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int x, int y, int width, int height, bool fullscreen)
{
	is_running = true;

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
			is_running = false;
			return;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		gl_context = SDL_GL_CreateContext(window);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) 
		{
			printf("Failed to initialize OpenGL context\n");
			is_running = false;
		}
		glEnable(GL_DEPTH_TEST);
		glInfo();
		initBasicProgram();
		initKeyboardState();

		projection_matrix = glm::perspective(glm::radians(60.0f), (float)width / (float)height, NEAR, FAR);
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
			is_running = false;
			break;
		case SDL_EVENT_MOUSE_MOTION:
			mouseMoveEvent(event.motion);
			break;
		case SDL_EVENT_KEY_DOWN:
			processKeyEvent(event.key.keysym.sym, true);
			break;
		case SDL_EVENT_KEY_UP:
			processKeyEvent(event.key.keysym.sym, false);
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	glm::vec2 dir = glm::vec2(0,0);
	//Check what keys are down
	for (std::map<Uint8, bool>::iterator it = keyboard_state.begin(); it != keyboard_state.end(); it++) 
	{
		if (it->second)
		{
			switch (it->first)
			{
			case SDLK_w:
				dir.x += 1;
				break;
			case SDLK_s:
				dir.x += -1;
				break;
			case SDLK_d:
				dir.y += 1;
				break;
			case SDLK_a:
				dir.y += -1;
				break;
			default:
				break;
			}
		}
	}
	if (glm::length(dir) > 0)
	{
		camera.updateCameraPosition(glm::normalize(dir));
	}
}

void Game::Render()
{
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CLIP_DISTANCE0);
	glUseProgram(basic_shader_program);
	glBindVertexArray(VAO);
	glUniformMatrix4fv(glGetUniformLocation(basic_shader_program, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
	glUniformMatrix4fv(glGetUniformLocation(basic_shader_program, "view_matrix"), 1, false, glm::value_ptr(camera.getViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(basic_shader_program, "transformation_matrix"), 1, false, glm::value_ptr(transformation_matrix));
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(window);
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

void Game::initKeyboardState()
{
	keyboard_state[SDLK_w] = false;
	keyboard_state[SDLK_a] = false;
	keyboard_state[SDLK_s] = false;
	keyboard_state[SDLK_d] = false;
}

void Game::processKeyEvent(Uint8 key, bool key_down)
{
	if (keyboard_state.find(key) != keyboard_state.end()) 
	{
		keyboard_state[key] = key_down;
	}
}
//TODO fix bug with movement and pitch yaw
void Game::mouseMoveEvent(SDL_MouseMotionEvent event)
{
	if (first_mouse)
	{
		lastX = event.x;
		lastY = event.y;
		first_mouse = false;
	}

	float xoffset = event.x - lastX;
	float yoffset = event.y - lastY;
	lastX = event.x;
	lastY = event.y;

	float sensitivity = 0.2f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.updatePitchYaw(xoffset, yoffset);
}

void Game::Quit()
{
	std::cout << "Quit Game" << std::endl;
	//SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
