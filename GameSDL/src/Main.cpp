#include <SDL3/SDL_main.h> // only include this one in the source file with main()!
#include "Game.h"

Game* game = nullptr;

//Window configuration
const char* TITLE = "Game SDL";
const unsigned int XPOS = SDL_WINDOWPOS_CENTERED;
const unsigned int YPOS = SDL_WINDOWPOS_CENTERED;
const int WIDTH = 800;
const int HEIGHT = 600;
const bool FULLSCREEN = false;

int main(int argc, char* argv[])
{
    game = new Game(TITLE, XPOS, YPOS, WIDTH, HEIGHT, FULLSCREEN);
    //game->Init();

    while (game->Running()) {
        game->Event();
        game->Update();
        game->Render();
    }

    game->Quit();

    return 0;
}