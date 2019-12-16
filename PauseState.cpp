#include "PauseState.h"
#include "Game.h"
const std::string PauseState::menuID = "PAUSE";
PauseState::PauseState(int areaw,int areah)
{
   this->startButton = new Button(areaw/3,(areah/4)*1,"continue.png");
this->startButton->show();
	SDL_RenderPresent(Game::getInstance()->getRenderer());
}

PauseState::~PauseState()
{
    //dtor
    delete startButton;
    
}
void PauseState::update()
{
	
	while(SDL_PollEvent(&Game::e))
			{
				if(Game::e.type == SDL_QUIT)
				{
					Game::getInstance()->End();
					break;
				}
	this->startButton->handle_events();

			}

			
			
	if(this->startButton->isClicked())
	{
		Game::getInstance()->getGSM()->popState();
	}
}
void PauseState::render()
{
}

