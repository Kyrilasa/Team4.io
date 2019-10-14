#include "Player.h"
#include "Tile.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include  <iostream>
using namespace std;
Player::Player(int _height,int _width, SDL_Color _color,string _name)
{
    srand (time(NULL));
    this->rectangle.x = (int)(rand() % (_width - 2) +1);
    this->rectangle.y = (int)(rand() % (_height - 2) +1);

    if(this->rectangle.x < 5)
    {
        this->rectangle.x += 5;
    }
    else if(this->rectangle.x > (_width -5))
    {
        this->rectangle.x-= 5;
    }
    if(this->rectangle.y < 5)
    {
        this->rectangle.y+= 5;
    }
    else if(this->rectangle.y > (_height) - 5)
    {
        this->rectangle.y -= 5;
    }
    this->color.r = _color.r;
    this->color.g = _color.g;
    this->color.b = _color.b;
    //Player's width and height
    this->rectangle.h=25;
    this->rectangle.w=25;
    gameAreaHeight = _height;
    gameAreaWidth = _width;
    this->name=_name;
    double randWay = rand()%5;
    if (randWay < 0.25)
    {
        this->dx = 1;
        this->dy = 0;
    }
    else if (randWay < 5)
    {
        this->dx = -1;
        this->dy = 0;
    }
    else if (randWay < 0.75)
    {
        this->dx = 0;
        this->dy = 1;
    }
    else
    {
        this->dx = 0;
        this->dy = -1;
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

}

void Player::die()
{


}


void Player::setTileO(Tile *t)
{
    this->tilesO.push_back(*t);
    t->setOwner(this);
    t->setContestedO(nullptr);
}


void Player::removeTileO(Tile t)
{

    for(std::vector<Tile>::iterator it = this->tilesO.begin(); it!=tilesO.end(); it++)
    {
        if(*it==t)
        {
            this->tilesO.erase(it);
        }
    }
}


vector<Tile> Player::getTilesO()
{
    return this->tilesO;
}

double Player::getPercentO()
{

    return 0;
}


void Player::setTileC(Tile t)
{
    t.setContestedO(this);
    this->tilesC.push_back(t);
}


vector<Tile> Player::getTilesC()
{
    return this->tilesC;
}


void Player::contestToO()
{
    for (Tile &t : this->tilesC)
    {
        this->setTileO(&t);
    }
    this->tilesC.erase(this->tilesC.begin(),this->tilesC.end());
}

void Player::checkCollision(Tile t)
{

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
    return 0;
}

