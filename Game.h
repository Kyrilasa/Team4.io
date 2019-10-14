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
        bool quit = false;

    protected:

    private:
        void initBoard();
        Tile* getTile(int x,int y);
        void startingArea(Player* player);
        bool checkSpawn(Player* player);
        int areaHeight;
        int areaWidth;
        vector<Player*> Players;
        map<Tile, Player> tilePlayerMap;
        vector<Tile*>gameArea;
};

#endif // GAME_H
