#include "Game.h"
#include <iostream>

//b static variables
vector<vector<Tile*>*>Game::gameArea;
bool Game::quit = false;
int Game::LEVEL_WIDTH = 1280;
int Game::LEVEL_HEIGHT = 960;
SDL_Rect Game::camera = {0,0,640,480};
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
    for(int i = 0; i < Game::LEVEL_HEIGHT/10; i++)
    {
        Game::gameArea.push_back(new vector<Tile*>());
        for(int j = 0; j < Game::LEVEL_WIDTH/10; j++)
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

            player->setTileO(getTile(i,j,this->areaWidth,this->areaHeight));
        }
    }
}

Tile* Game::getTile(int x,int y,int gameAreaWidth,int gameAreaHeight)
{
    //TODO get rid of this
    if(x>=Game::LEVEL_WIDTH)
    {
        return Game::gameArea.at(y/10)->at((x-10)/10);
    }
    if(x<0)
    {
        return Game::gameArea.at(y/10)->at((x+10)/10);
    }
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
    }
    //e render Tiles

    //b render Player
    this->ThePlayer->render(this->renderer);
    //e render Player


}

void Game::fillContested(Player* player,int gameAreaWidth,int gameAreaHeight) {
        int maxX = 0;
        int minX = gameAreaWidth;
        int maxY = 0;
        int minY = gameAreaHeight;
        for (auto t : player->getTilesO()) {
            if(t->getX() > maxX) maxX = t->getX();
            if(t->getX() < minX) minX = t->getX();
            if(t->getY() > maxY) maxY = t->getY();
            if(t->getY() < minY) minY = t->getY();
        }
        //if player reconnect to base from the right.
        if(Game::getTile(minX-10,minY,gameAreaWidth,gameAreaHeight)->getOwner()==player)
        {
            minX-=10;
        }

        vector<Tile*> needToFill;
    for(auto i = minY;i<=maxY;i+=10)
    {
            for(auto j= minX;j<=maxX;j+=10)
            {
                Tile *tmpTile = Game::getTile(j,i,gameAreaWidth,gameAreaHeight);

                if((tmpTile->getOwner()==player))
                {
                    if(Game::getTile(j+10,i,gameAreaWidth,gameAreaHeight)->getOwner()==nullptr)
                    {
//                        case
//                        100000001111000|
//                        where contested is 1 ,| is the border and 0 needs to be filled with player color

                        Tile* startNode = Game::getTile(j,i,gameAreaWidth,gameAreaHeight);
                        while(Game::getTile(j+10,i,gameAreaWidth,gameAreaHeight)->getOwner()==nullptr&&(j+10)<=maxX)
                        {
                        j+=10;
                        }
                        Tile* endNode = Game::getTile(j+10,i,gameAreaWidth,gameAreaHeight);


                        if(endNode->getOwner()!=nullptr||endNode->getOwner()==player)
                        {
                            for(auto z = startNode->getX();z<=endNode->getX();z+=10)
                              {
                                needToFill.push_back(Game::getTile(z,i,gameAreaWidth,gameAreaHeight));
                              }
                        }
                    }else if(Game::getTile(j+10,i,gameAreaWidth,gameAreaHeight)->getOwner()==player)
                    {
                        continue;
                    }
                }


            }
    }
    for(auto t:needToFill)
    {
        player->setTileO(t);

    }



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
