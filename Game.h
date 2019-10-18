#ifndef GAME_H
#define GAME_H
#include "Tile.h"
#include "Player.h"
#include <map>
class Game
{
    public:
        Game(int areaHeight,int areaWidth,string playerName,SDL_Window *window);
        virtual ~Game();
        void render();
        void update(SDL_Event e);
        SDL_Renderer* renderer = nullptr;

        static bool quit;
        static Tile* getTile(int x,int y);
        static vector<vector<Tile*>*>gameArea;

    protected:

    private:
        void initBoard();
        void startingArea(Player* player);
        void fillContested(Player* player);
         int areaHeight;
         int areaWidth;
//        vector<Player*> Players;
        Player* ThePlayer;
        map<Tile, Player> tilePlayerMap;
};

#endif // GAME_H
