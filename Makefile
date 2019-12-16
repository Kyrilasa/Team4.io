CC = g++
CFLAGS = -Wall -lSDL2 -lSDL2_image

all:
	$(CC) main.cpp Game.cpp Button.cpp GameState.cpp  GameStateMachine.cpp MenuState.cpp PlayState.cpp  PauseState.cpp  Player.cpp Tile.cpp $(CFLAGS) -o Team4io
clean:
	rm -rf *o Team4io

