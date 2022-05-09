
#include "Game.h"
#include "SDL.h"
#include <iostream>

int main()
{

	CGame* Gamemode = new CGame;

	Gamemode->startGame();

	Gamemode->GenerateLevel();

	bool CanStartGame ;

	if (Gamemode->startRender() && Gamemode->startInput())
		CanStartGame = true;
	else
		CanStartGame = false;

	if (CanStartGame == true)
		Gamemode->startGameLoop();

	delete Gamemode;

	int a;

	std::cin >> a;

	return 0;
}