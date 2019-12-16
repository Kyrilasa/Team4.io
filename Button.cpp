#include "Button.h"
#include "Game.h"
#include "SDL2/SDL_image.h"

using namespace std;

Button::Button( int x, int y,char* path )
{
    //Set the button's attributes
    this->path = path;
	box.x = x;
    box.y = y;
clicked = false;
}
Button::~Button()
{

}
SDL_Rect* Button::getBox()
{
    return &this->box;
}
void Button::handle_events()
{
    //The mouse offsets
    int x = 0, y = 0;
    SDL_GetMouseState(&x,&y);
    //If a mouse button was pressed
    if( Game::e.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( Game::e.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = Game::e.button.x;
            y = Game::e.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                //Close the menu
                clicked = true;

                //Check other players
            }
        }
    }

}

void Button::show()
{
    SDL_Surface* surface = IMG_Load(path);
    texture =  SDL_CreateTextureFromSurface(Game::getInstance()->getRenderer(),surface);
    SDL_FreeSurface(surface);
    int w,h;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    box.w = w;
    box.h = h;
	SDL_RenderCopy(Game::getInstance()->getRenderer(),texture,NULL,&box);
}
bool Button::isClicked()
{
	return this->clicked;
}
