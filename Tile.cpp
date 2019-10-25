#include "Tile.h"
Tile::Tile(int x, int y,SDL_Color _color)
{

    this->color.r = _color.r;
    this->color.g = _color.g;
    this->color.b = _color.b;
    this->rectangle.x = x;
    this->rectangle.y = y;
    this->rectangle.w=10;
    this->rectangle.h=10;
    this->owner=nullptr;
    this->contestedO = nullptr;
}

Tile::~Tile()
{
    //dtor
}
SDL_Color Tile::getColor()
{
    if(this->getOwner()&&!this->getContestedO())
    {
    return this->getOwner()->getColor();
    }else if(this->getOwner()&&this->getContestedO())
    {
        SDL_Color c;
        c.a = 100;
        c.r = this->getContestedO()->getColor().r;
        c.g = this->getContestedO()->getColor().g;
        c.b = this->getContestedO()->getColor().b;
    return c;
    }else if(!this->getOwner()&&this->getContestedO())
    {
        SDL_Color c;
        c.a = 100;
        c.r = this->getContestedO()->getColor().r;
        c.g = this->getContestedO()->getColor().g;
        c.b = this->getContestedO()->getColor().b;
        return c;
    }else
    {
        return this->color;
    }
}
Player* Tile::getContestedO()
{
    return this->contestedO;
}
void Tile::setContestedO(Player *contestedOwner)
{
    this->contestedO = contestedOwner;
}
Player* Tile::getOwner()
{
    return this->owner;
}
void Tile::setOwner(Player *owner)
{

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
void Tile::render(SDL_Renderer *_rend)
{
        //camera
        SDL_Rect rectangleTmp;
        rectangleTmp.x = rectangle.x-Game::camera.x;
        rectangleTmp.h = rectangle.h;
        rectangleTmp.w = rectangle.w;
        rectangleTmp.y = rectangle.y-Game::camera.y;
                    SDL_SetRenderDrawColor( _rend, this->getColor().r, this->getColor().g,this->getColor().b,100);
                    SDL_RenderFillRect( _rend, &rectangleTmp );
}

