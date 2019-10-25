#include "Game.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <time.h>
#include <map>
//b static variables
vector<vector<Tile*>>Game::gameArea;
SDL_Event Game::e;
bool Game::quit = false;
int Game::LEVEL_WIDTH = 1280;
int Game::LEVEL_HEIGHT = 960;
SDL_Rect Game::camera = {0,0,640,480};
//e static variables
std::string random_id( size_t length )
{
    srand (time(NULL));
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}
Game::Game(int areaHeight,int areaWidth,string playerName,SDL_Window *window)
{

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    this->areaHeight = areaHeight;
    this->areaWidth = areaWidth;
    this->ThePlayer = new Player(areaHeight, areaWidth,random_id(10));

//    for(int i = 0;i<10;i++)
//    {
//        this->Players.push_back(new Player(areaHeight,areaWidth,random_id(15 )));
//    }
    initBoard();

}

Game::~Game()
{
    for(auto k:gameArea)
    {
        for(auto p:k)
        {
            delete p;
        }
    }
    delete ThePlayer;
}
void Game::initBoard()
{
    //render tiles for the first time && get starting zone around  player...
    for(int i = 0; i < Game::LEVEL_HEIGHT/10; i++)
    {
        Game::gameArea.push_back(vector<Tile*>());
        for(int j = 0; j < Game::LEVEL_WIDTH/10; j++)
        {
            Game::gameArea[i].push_back(new Tile(j*10,i*10,{150,10,255}));
            Game::gameArea[i].back()->render(this->renderer);

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
        return Game::gameArea.at(y/10).at((x-10)/10);
    }
    if(x<0)
    {
        return Game::gameArea.at(y/10).at((x+10)/10);
    }
    if(y>=Game::LEVEL_HEIGHT)
    {
        return Game::gameArea.at((y-10)/10).at((x)/10);
    }
    if(y<0)
    {
        return Game::gameArea.at((y+10)/10).at((x)/10);
    }
    return Game::gameArea.at(y/10).at(x/10);
}
void Game::render()
{

    //b render Tiles
    //TODO render optimization to render only what is visible for player instead of whole map
    int counter=0;
 for(auto &p:gameArea)
    {

        vector<Tile*> tmp(p.begin(),p.end());
        //check if the y coordinate of the tile vector column visible to player
            int pYp=ThePlayer->getY()+(Game::camera.h/2);
            int pYm=ThePlayer->getY()-(Game::camera.h/2);
            int kY=tmp[0]->getY();
            if(pYp>Game::LEVEL_HEIGHT)
            {
                pYm -=(pYp-Game::LEVEL_HEIGHT);
                pYp = Game::LEVEL_HEIGHT;
            }
            if(pYm<0)
            {
                pYp+=(-1*pYm);
                pYm=0;
            }

            if((kY<=pYp)&&(kY>=pYm))
            {
        for(auto k:tmp)
        {

        //check if the x coordinate of the tile vector row visible to player
            int kX=k->getX();
            int pXp=ThePlayer->getX()+(Game::camera.w/2);
            int pXm=ThePlayer->getX()-(Game::camera.w/2);
            if(pXp>Game::LEVEL_WIDTH)
            {
                pXm -=(pXp-Game::LEVEL_WIDTH);
                pXp = Game::LEVEL_WIDTH;

            }
            if(pXm<0)
            {
                pXp+=(-1*pXm);
                pXm=0;
            }
            if((kX>=pXm)&&(kX<=pXp))
            {
            k->render(this->renderer);
            counter++;
            }
        }
            }
    }
    //e render Tiles

    //b render Player
    this->ThePlayer->render(this->renderer);
    //e render Player


}

void Game::fillContested(Player* player,int gameAreaWidth,int gameAreaHeight) {
    //go through horizontally and vertically if
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
        map<Tile*,int> needToFillMap;
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
                                needToFillMap[Game::getTile(z,i,gameAreaWidth,gameAreaHeight)]++;
                              }
                        }
                    }
                }


            }
    }

    for(auto i = minX;i<=maxX;i+=10)
    {
            for(auto j= minY;j<=maxY;j+=10)
            {
                Tile *tmpTile = Game::getTile(i,j,gameAreaWidth,gameAreaHeight);

                if((tmpTile->getOwner()==player))
                {
                    if(Game::getTile(i,j+10,gameAreaWidth,gameAreaHeight)->getOwner()==nullptr)
                    {
                        Tile* startNode = Game::getTile(i,j,gameAreaWidth,gameAreaHeight);
                        while(Game::getTile(i,j+10,gameAreaWidth,gameAreaHeight)->getOwner()==nullptr&&(j+10)<=maxY)
                        {
                        j+=10;
                        }
                        Tile* endNode = Game::getTile(i,j+10,gameAreaWidth,gameAreaHeight);


                        if(endNode->getOwner()!=nullptr||endNode->getOwner()==player)
                        {
                            for(auto z = startNode->getY();z<=endNode->getY();z+=10)
                              {
                                needToFillMap[Game::getTile(i,z,gameAreaWidth,gameAreaHeight)]++;
                              }
                        }
                    }
                }


            }
    }

    for(auto t:needToFillMap)
    {
        if(t.second>1)
        {

        player->setTileO(t.first);
        }
    }
}

//Main game logic
void Game::update()
{

        while( SDL_PollEvent(&Game::e)!=0)
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
                    if(this->ThePlayer->dx != 10)
                    {
                    this->ThePlayer->dx = -10;
                    this->ThePlayer->dy= 0;
                    }
                    break;
                case SDLK_RIGHT:
                    if(this->ThePlayer->dx != -10)
                    {
                    this->ThePlayer->dx= 10;
                    this->ThePlayer->dy=0;
                    }
                    break;
                case SDLK_UP:
                    if(this->ThePlayer->dy != 10)
                    {
                    this->ThePlayer->dx= 0;
                    this->ThePlayer->dy=-10;
                    }
                    break;
                case SDLK_DOWN:
                    if(this->ThePlayer->dy != -10)
                    {
                    this->ThePlayer->dx= 0;
                    this->ThePlayer->dy=10;
                    }
                    break;
                default:
                    break;
                }
            }

        }
//        for(auto t:this->Players)
//    {
//        t->update();
//    }
this->ThePlayer->update();
}
