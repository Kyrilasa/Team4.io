#ifndef PAUSESTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Button.h"

class PauseState : public GameState
{
    public:
        PauseState(int areaw,int areah);
        virtual ~PauseState();
        virtual void update();
        virtual void render();
//        virtual bool onEnter();
//        virtual bool onExit();
        virtual std::string getStateId()const{return menuID;};
    private:
        const static std::string menuID;
        Button* startButton;
        Button* exitButton;
};

#endif // PAUSESTATE_H
