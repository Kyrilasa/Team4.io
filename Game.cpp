#include "Game.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <unordered_set>
#include <stack>
#include <algorithm>

//b static variables
vector<vector<Tile*>*>Game::gameArea;
bool Game::quit = false;
//e static variables

Game::Game(int areaHeight,int areaWidth,string playerName,SDL_Window *window)
{

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    this->areaHeight = areaHeight;
    this->areaWidth = areaWidth;
    this->ThePlayer = new Player(areaHeight, areaWidth, {0,0,255},playerName);

    initBoard();

}

Game::~Game()
{
    //dtor
}
void Game::initBoard()
{
    //render tiles for the first time && around  player...
    for(int i = 0; i < areaHeight/10; i++)
    {
        Game::gameArea.push_back(new vector<Tile*>());
        for(int j = 0; j < areaWidth/10; j++)
        {
            Game::gameArea[i]->push_back(new Tile(j*10,i*10,{150,10,255}));
            Game::gameArea[i]->back()->render(this->renderer);

        }
    }
    startingArea(this->ThePlayer);
    SDL_RenderPresent(this->renderer);

}
//draws 1-1 tile-owned around player
void Game::startingArea(Player* player)
{
    int x = player->getX();
    int y = player->getY();

    for(int i = x-10; i <= x+10; i+=10)
    {
        for(int j = y-10; j <= y+10; j+=10)
        {

            player->setTileO(getTile(i,j));
        }
    }
}

Tile* Game::getTile(int x,int y)
{

    return Game::gameArea.at(y/10)->at(x/10);
}
void Game::render()
{
    //b render Tiles
    for(auto p:this->gameArea)
    {
        vector<Tile*> tmp(p->begin(),p->end());
        for(auto k:tmp)
        {
            k->render(this->renderer);
        }
    }SDL_RenderPresent(this->renderer);
    //e render Tiles

    //b render Player
    this->ThePlayer->render(this->renderer);
    //e render Player


}

void Game::fillContested(Player* player) {

    }

//Main game logic
void Game::update(SDL_Event e)
{

        while( SDL_PollEvent(&e)!=0)
        {
            if( e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    this->ThePlayer->dx = -10;
                    this->ThePlayer->dy= 0;
                    break;
                case SDLK_RIGHT:
                    this->ThePlayer->dx= 10;
                    this->ThePlayer->dy=0;
                    break;
                case SDLK_UP:
                    this->ThePlayer->dx= 0;
                    this->ThePlayer->dy=-10;
                    break;
                case SDLK_DOWN:
                    this->ThePlayer->dx= 0;
                    this->ThePlayer->dy=10;
                    break;
                default:
                    break;
                }
            }

        }
this->ThePlayer->update();





}
