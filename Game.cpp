#include "Game.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
Game::Game(int areaHeight,int areaWidth,string playerName,SDL_Window *window)
{

    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    this->areaHeight = areaHeight;
    this->areaWidth = areaWidth;
    this->Players.push_back(new Player(areaHeight, areaWidth, {0,0,255},playerName));

    initBoard();

//        initBoard();
//
//        painters.add(new Painter(scale, this, humanPlayers.get(0), players));
//        player_painter.put(humanPlayers.get(0), painters.get(0));
}

Game::~Game()
{
    //dtor
}
void Game::initBoard()
{

    srand (time(NULL));

    auto renderTiles = [](SDL_Renderer* _rend,Tile* k)
    {

                    SDL_SetRenderDrawColor( _rend, k->getColor().r, k->getColor().g,k->getColor().b, 255 );
                    SDL_RenderFillRect( _rend, &k->rectangle );
                    SDL_RenderPresent(_rend);

    };
    for(int i = 0; i < areaHeight/25+2; i++)
    {
        for(int j = 0; j < areaWidth/25+2; j++)
        {
            this->gameArea.push_back(new Tile(j*25,i*25,{255,255,255}));
            renderTiles(this->renderer,gameArea.back());
        }
    }

}
void Game::startingArea(Player* player)
{
    int x = player->getX();
    int y = player->getY();
    for(int i = x-1; i <= x+1; i++)
    {
        for(int j = y-1; j <= y+1; j++)
        {
            player->setTileO(getTile(i,j));
        }
    }
}
bool Game::checkSpawn(Player* player)
{
    int x = player->getX();
    int y = player->getY();
    for(int i = x-3; i <= x+3; i++)
    {
        for (int j = y - 3; j <= y + 3; j++)
        {
            if (getTile(i, j)->getOwner() != nullptr || getTile(i, j)->getContestedO() != nullptr )
            {
                return false;
            }
        }
    }
    return true;
}
Tile* Game::getTile(int x,int y)
{
    return gameArea[y];
}
void Game::render()
{
//    auto renderBackground = [](SDL_Renderer* _rend)
//    {
//        SDL_SetRenderDrawColor( _rend, 255, 0, 0, 255 );
//        SDL_RenderClear( _rend);
//    };

    auto renderPlayer = [](SDL_Renderer* _rend,Player *r)
    {

        SDL_SetRenderDrawColor( _rend, r->getColor().r, r->getColor().g,r->getColor().b, 255 );
        SDL_RenderFillRect( _rend, &r->rectangle );
        SDL_RenderPresent(_rend);
    };
    for(auto p:this->Players)
    {
        renderPlayer(this->renderer,p);
    }

}
void Game::update(SDL_Event e)
{
    for(auto p:this->Players)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_LEFT:
                    p->dx = -1;
                    p->dy= 0;
                    break;
                case SDLK_RIGHT:
                    p->dx= 1;
                    p->dy=0;
                    break;
                case SDLK_UP:
                    p->dx= 0;
                    p->dy=-1;
                    break;
                case SDLK_DOWN:
                    p->dx= 0;
                    p->dy=1;
                    break;
                default:
                    break;
                }
            }


        }
        if(p->dx==-1)
        {
            p->rectangle.x-=10;
        }
        else if(p->dx==1)
        {
            p->rectangle.x+=10;
        }
        else if(p->dy==-1)
        {
            p->rectangle.y-=10;
        }
        else if(p->dy==1)
        {
            p->rectangle.y+=10;
        }
    }
}
