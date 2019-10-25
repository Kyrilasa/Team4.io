#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
using namespace std;
#define BLUE {0,0,255}
const int WIDTH = 640;
const int HEIGHT = 480;
int main(int argc,char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Team4io",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WIDTH, HEIGHT,
                                          0);

    if(!window)
    {
        std::cout << "Failed to create window\n";
        return -1;
    }

    SDL_Event e;
    Game game(HEIGHT,WIDTH,"dummy",window);
//    gameloop
    while(!Game::quit)
    {

                game.update();
                game.render();
                SDL_Delay(16);
    }
    SDL_Quit();
    return 0;
}
