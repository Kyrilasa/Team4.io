#include "PlayState.h"
#include "Game.h"
#include "iostream"

const std::string PlayState::playID = "PLAY";
PlayState::PlayState()
{
    //ctor
}

PlayState::~PlayState()
{
    //dtor
}
void PlayState::update()
{

	Game::getInstance()->innerUpdateP();
}
void PlayState::render()
{

	Game::getInstance()->innerRenderP();
}

