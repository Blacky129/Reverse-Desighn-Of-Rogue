#pragma once

#include "CActorsStack.h"
#include "Map/CMap.h"
#include "Screen.h"
#include "Hero.h"
#include "CGameLogic.h"

#include "./Actor/Controller/Input/InputManager.h" //TODO Remove

class CGame
{
private:

	const int DEFAULT_COUNT_OF_ROOM = 9;

	int Level = 0;

	CScreen* Screen;

	CMap* GameMap;

	CGameLogic* GameLogic;

	CHero* Player;

	CInputManager* KeyboardInput;

	CActorStack* ActorsStack;

public:
	//main
	void startGame();

	void getPlayerInput();

	//end main
	CGame();

	~CGame();

	//React on input
	void getInput();

	void provideGameLogic();

	void moveHero(InputType Direction);

	//Create dungeon
	void GenerateLevel();

	//Try to create Window
	bool startRender();

	//Try to init SDL input
	bool startInput();

	//Input -> GameLogic -> Render
	void startGameLoop();

	void renderGraphic();

private:
	bool isRunning;

	void exitLevel();
};