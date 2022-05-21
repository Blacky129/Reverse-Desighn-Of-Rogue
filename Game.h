#pragma once

#include "IObsever.h"
#include "CActorsStack.h"
#include "Map/CMap.h"
#include "Screen.h"
#include "CGameLogic.h"
#include "CPathFinder.h"

class CGame : public IObserver
{
private:

	const int DEFAULT_COUNT_OF_ROOM = 9;

	int Level = 0;

	CScreen* Screen;

	CMap* GameMap;

	CGameLogic* _GameLogic;

	CActorStack* _ActorsStack;

	CPathFinder* _PathFinder;

	bool isRunning;
public:
	void startGame();

	void getPlayerInput();

	CGame();

	~CGame();

	void provideGameLogic();

	void GenerateLevel();

	//Try to create Window
	bool startRender();

	//Input -> GameLogic -> Render
	void startGameLoop();

	void renderGraphic();

	void onNotify(EVENT_TYPE Event);
private:
};