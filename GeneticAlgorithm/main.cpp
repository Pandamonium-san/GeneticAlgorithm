#include <iostream>
#include "Game.h"

Game game(800, 600, "AI test");

int main()
{
	game.RunGameLoop();
	return 0;
}