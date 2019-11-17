#include "Button.h"
#include "Game.h"
Button::Button( int x, int y, int w, int h )
{
    //Set the button's attributes
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;

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
                Game::inMenu=false;
            }
        }
    }

}

void Button::show()
{
    SDL_SetRenderDrawColor(Game::getInstance()->getRenderer(),100,100,100,255);
    SDL_RenderFillRect(Game::getInstance()->getRenderer(),&this->box);
    SDL_RenderPresent(Game::getInstance()->getRenderer());
}

