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
    this->rectangle.x = RoundNum(round((int)(rand() % ((_width)) +1)),10);
    this->rectangle.y = RoundNum(round((int)(rand() % (_height) +1)),10 );

    if(this->rectangle.x < 0)
    {
        this->rectangle.x += 10;
    }
    else if(this->rectangle.x > (_width-10))
    {
        this->rectangle.x-= 10;
    }
    if(this->rectangle.y < 10)
    {
        this->rectangle.y+= 10;
    }
    else if(this->rectangle.y > (_height) - 10)
    {
        this->rectangle.y -= 10;
    }
    this->color.r = _color.r;
    this->color.g = _color.g;
    this->color.b = _color.b;
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
    return this->color;
}

void Player::move()
{
    std::cout<<getX()<<" "<<getY()<<std::endl;
    this->rectangle.x+=dx;
    this->rectangle.y+=dy;
}

void Player::die()
{
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
    return 100 * this->getTilesO().size() / (double)(this->gameAreaHeight*this->gameAreaWidth)/10;
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
    }
    this->tilesC.erase(this->tilesC.begin(),this->tilesC.end());
}

void Player::checkCollision(Tile* t)
{
    if(t->getContestedO() != nullptr)
    {
        t->getContestedO()->die();
        std::cout<<"halal"<<std::endl;
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
            if(this->getX() < 0 || this->getX() >= gameAreaWidth || this->getY() < 0 || this->getY() >= gameAreaHeight){
                this->die();

            }else{
                Tile* tile = Game::getTile(this->getX(), this->getY());
                this->checkCollision(tile);
                this->setCurrentTile(tile);
                if (tile->getOwner() != this) {
                    this->setTileC(tile);
                } else if (this->getTilesC().size() > 0) {
                    this->contestToO();
                  //TODO fillContested(this);

                }
            }
}
void Player::render(SDL_Renderer *_rend)
{

        SDL_SetRenderDrawColor( _rend, this->getColor().r, this->getColor().g,this->getColor().b, 255 );
        SDL_RenderDrawRect( _rend, &this->rectangle );
        SDL_RenderPresent(_rend);
}
