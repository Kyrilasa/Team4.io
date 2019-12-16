#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <iostream>


class Button
{
    private:
    //The attributes of the button
    SDL_Rect box;
 const  char* path;
    public:
    //Initialize the variables
    Button( int x, int y,const char* path );
   ~Button();
    SDL_Rect* getBox();
    SDL_Texture* texture;
    //Handles events and set the button's sprite region
    void handle_events();
bool isClicked();
    bool clicked;
    //Shows the button on the screen
    void show();
    enum button_state
    {
        MOUSE_OUT,MOUSE_OVER,CLICKED
    };
};

#endif // BUTTON_H
