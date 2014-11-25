/*
	ASTEROIDS
	Clone of the classic game

	Features:
		* online highscore table

	@author Marcin Chudy
	@version 1.0
*/


#include <cstdlib>
#include "Game.h"

int main()
{
	srand(unsigned(time(nullptr)));
	Game game;
	game.run();
	return 0;
} 