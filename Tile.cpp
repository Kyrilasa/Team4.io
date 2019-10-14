#include "Tile.h"
#include "Player.h"
#include <iostream>
Tile::Tile(int x, int y,SDL_Color _color)
{

    this->color.r = _color.r;
    this->color.g = _color.g;
    this->color.b = _color.b;
    this->rectangle.x = x;
    this->rectangle.y = y;
    this->rectangle.w=25;
    this->rectangle.h=25;
}

Tile::~Tile()
{
    //dtor
}
SDL_Color Tile::getColor()
{

    return this->color;
}
Player* Tile::getContestedO()
{
    return this->contestedO;
}
void Tile::setContestedO(Player *contestedOwner)
{
    this->contestedO = contestedOwner;
}
Player Tile::getOwner()
{
    return *this->owner;
}
void Tile::setOwner(Player *owner)
{
    if(this->owner != nullptr)
    {
        this->owner->removeTileO(*this);
    }
    this->owner = owner;
}

int Tile::getX()
{
    return this->rectangle.x;
}

int Tile::getY()
{
    return this->rectangle.y;
}
