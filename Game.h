#ifndef GAME_H
#define GAME_H
#include "Tile.h"
#include "Player.h"
class Game
{
    public:
        Game(int areaHeight,int areaWidth,string playerName,SDL_Window *window);
        virtual ~Game();
        void render();
        void update(SDL_Event e);
        SDL_Renderer* renderer = nullptr;
        //static variables
        static SDL_Rect camera;
        static int LEVEL_WIDTH ;
        static int LEVEL_HEIGHT ;
        static bool quit;
        static Tile* getTile(int x,int y,int gameAreaWidth,int gameAreaHeight);
        static void fillContested(Player* player,int gameAreaWidth,int gameAreaHeight);
        static vector<vector<Tile*>*>gameArea;
        //
    protected:

    private:
        void initBoard();
        void startingArea(Player* player);
         int areaHeight;
         int areaWidth;
//        vector<Player*> Players;
        Player* ThePlayer;
};

#endif // GAME_H
