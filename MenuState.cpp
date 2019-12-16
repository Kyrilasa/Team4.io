#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
#include <SDL2/SDL_events.h>
const std::string MenuState::menuID = "MENU";
MenuState::MenuState(int screenwidth,int screenheight)
{
   this->startButton = new Button(screenwidth/3,(screenheight/4)*1,"play.png");
   this->exitButton = new Button(screenwidth/3,(screenheight/4)*2,"exit.png");
}

MenuState::~MenuState()
{
    //dtor
    delete startButton;
    delete exitButton;
}
void MenuState::update()
{
	
	while(SDL_PollEvent(&Game::e))
			{
				if(Game::e.type == SDL_QUIT)
				{
					Game::getInstance()->End();
					break;
				}
	this->startButton->handle_events();
	this->exitButton->handle_events();
			}

			
			
	if(this->startButton->isClicked())
	{
		Game::getInstance()->getGSM()->changeState(new PlayState());
	}
	if(this->exitButton->isClicked())
	{
		Game::getInstance()->End();
	}
}
void MenuState::render()
{
	this->startButton->show();
	this->exitButton->show();

	SDL_RenderPresent(Game::getInstance()->getRenderer());
}

