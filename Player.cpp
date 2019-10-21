#include "Player.h"
#include "Tile.h"
#include "Game.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include  <iostream>
#include <math.h>
using namespace std;
int RoundNum(int num, int step)
{
    if (num >= 0)
        return ((num + (step / 2)) / step) * step;
    else
        return ((num - (step / 2)) / step) * step;
}
Player::Player(int _height,int _width, SDL_Color _color,string _name)
{
    srand (time(NULL));
    this->rectangle.x = RoundNum(round((int)(rand() % ((Game::LEVEL_WIDTH)) +1)),10);
    this->rectangle.y = RoundNum(round((int)(rand() % (Game::LEVEL_HEIGHT) +1)),10 );

    if(this->rectangle.x < 0)
    {
        this->rectangle.x += 10;
    }
    else if(this->rectangle.x > (Game::LEVEL_WIDTH-10))
    {
        this->rectangle.x-= 10;
    }
    if(this->rectangle.y < 10)
    {
        this->rectangle.y+= 10;
    }
    else if(this->rectangle.y > (Game::LEVEL_HEIGHT) - 10)
    {
        this->rectangle.y -= 10;
    }
    this->tileColor.r = _color.r;
    this->tileColor.g = _color.g;
    this->tileColor.b = _color.b;
    //Player's width and height
    this->rectangle.h=10;
    this->rectangle.w=10;
    gameAreaHeight = _height;
    gameAreaWidth = _width;
    this->name=_name;
    double randWay = rand()%5;
    if (randWay < 0.25)
    {
        this->dx = 10;
        this->dy = 0;
    }
    else if (randWay < 5)
    {
        this->dx = -10;
        this->dy = 0;
    }
    else if (randWay < 0.75)
    {
        this->dx = 0;
        this->dy = 10;
    }
    else
    {
        this->dx = 0;
        this->dy = -10;
    }

}

Player::~Player()
{
    //dtor
}
int Player::getX()
{
    return this->rectangle.x;
}

int Player::getY()
{
    return this->rectangle.y;
}

SDL_Color Player::getColor()
{
    return this->tileColor;
}

void Player::move()
{
    this->rectangle.x+=dx;
    this->rectangle.y+=dy;
}

void Player::die()
{
    std::cout<<"Player named: "<<this->name<<" died. The owned area was: "<<this->getPercentO()<<"%"<<std::endl;
    isAlive = false;
    Game::quit = true;
    for(auto oTC :tilesO)
    {
        oTC->setOwner(nullptr);
    }

    for(auto cTC:tilesC)
    {
        cTC->setContestedO(nullptr);
    }
    this->tilesO.clear();
    this->tilesC.clear();
    this->currentTile = nullptr;
}


void Player::setTileO(Tile *t)
{
    this->tilesO.push_back(t);
    t->setOwner(this);
    t->setContestedO(nullptr);
}


void Player::removeTileO(Tile* t)
{

    for(std::vector<Tile*>::iterator it = this->tilesO.begin(); it!=tilesO.end(); it++)
    {
        if(*it==t)
        {
            this->tilesO.erase(it);
        }
    }
}


vector<Tile*> Player::getTilesO()
{
    return this->tilesO;
}

double Player::getPercentO()
{
    return (double)this->getTilesO().size()*100/(Game::LEVEL_HEIGHT*Game::LEVEL_WIDTH/100);
}


void Player::setTileC(Tile* t)
{
    t->setContestedO(this);
    this->tilesC.push_back(t);
}


vector<Tile*> Player::getTilesC()
{
    return this->tilesC;
}


void Player::contestToO()
{
    for (auto t : this->tilesC)
    {
        this->setTileO(t);
    	t->setContestedO(nullptr);
    }
    this->tilesC.erase(this->tilesC.begin(),this->tilesC.end());
}

void Player::checkCollision(Tile* t)
{
    if(t->getContestedO() != nullptr)
    {
        t->getContestedO()->die();
    }
}


void Player::setCurrentTile(Tile *currentTile)
{
    this->currentTile = currentTile;
}


int Player::getDx()
{
    return this->dx;
}

int Player::getDy()
{
    return this->dy;
}


string Player::getName()
{
    return this->name;
}

bool Player::getAlive()
{
    return this->isAlive;
}


void Player::setAlive(bool alive)
{
    this->isAlive = alive;
}


int Player::compareTo(Player *player)
{
    return (player->getTilesO().size()<this->tilesO.size()?1:-1);
}
void Player::update()
{
            this->move();
            Game::camera.x = ( getX() + this->rectangle.h / 2 ) - this->gameAreaWidth / 2;
            Game::camera.y = ( getY() + this->rectangle.h / 2 ) - this->gameAreaHeight / 2;

    if( Game::camera.x < 0 )
    {
        Game::camera.x = 0;
    }
    if( Game::camera.y < 0 )
    {
        Game::camera.y = 0;
    }
    if( Game::camera.x > Game::LEVEL_WIDTH - Game::camera.w )
    {
        Game::camera.x = Game::LEVEL_WIDTH - Game::camera.w;
    }
    if( Game::camera.y > Game::LEVEL_HEIGHT - Game::camera.h )
    {
        Game::camera.y = Game::LEVEL_HEIGHT - Game::camera.h;
    }
            if(this->getX() < 0 || this->getX() >= Game::LEVEL_WIDTH || this->getY() < 0 || this->getY() >= Game::LEVEL_HEIGHT){
                this->die();

            }else{
                Tile* tile = Game::getTile(this->getX(), this->getY(),gameAreaWidth,gameAreaHeight);
                this->checkCollision(tile);
                this->setCurrentTile(tile);
                if (tile->getOwner() != this) {
                    this->setTileC(tile);
                } else if (this->getTilesC().size() > 0) {
this->contestToO();
                    Game::fillContested(this,this->gameAreaWidth,this->gameAreaHeight);


                }
            }
}
void Player::render(SDL_Renderer *_rend)
{
        SDL_SetRenderDrawColor( _rend, this->color.r, this->color.g,this->color.b, 255 );
        //camera
        SDL_Rect rectangleTmp;
        rectangleTmp.x = rectangle.x-Game::camera.x;
        rectangleTmp.h = rectangle.h;
        rectangleTmp.w = rectangle.w;
        rectangleTmp.y = rectangle.y-Game::camera.y;
        SDL_RenderDrawRect(_rend,&rectangleTmp);
        SDL_RenderPresent(_rend);
}
