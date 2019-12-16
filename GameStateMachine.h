#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H
#include "GameState.h"
#include <stack>
class GameStateMachine
{
    public:
        GameStateMachine();
        virtual ~GameStateMachine();
        void pushState(GameState* state);
        void popState();
        void changeState(GameState* state);
	GameState* getCurrent();
    private:
        std::stack<GameState*> gameStates;
};

#endif // GAMESTATEMACHINE_H
