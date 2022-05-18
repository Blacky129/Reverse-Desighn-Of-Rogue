#include "Game.h"
#include"Map/CMapGenerator.h"

#include <iostream> //TODO For Debug

CGame::CGame()
{
	ActorsStack = new CActorStack;
	GameLogic = new CGameLogic;
	Screen = new CScreen;
	GameMap = nullptr;
	_PathFinder = new CPathFinder;
	isRunning = true;
}

void CGame::startGame()
{
	if (Screen->initSDL() == false)
		return;

	if (ActorsStack->createPlayer() == false)
		return;
	
	//TODO: Intro 

	GenerateLevel();

	startGameLoop();
}


CGame::~CGame()
{
	delete Screen;
	delete GameMap;
	delete _PathFinder;
}

bool isWindowsSizeOrPositionChanges(CPosition PrevWindowSize, CPosition NewWindowSize,
	CPosition PrevWindowPosition, CPosition NewWindowPosition)
{
	if (PrevWindowPosition == NewWindowPosition && PrevWindowSize == NewWindowSize)
		return false;
	return true;
}

void CGame::GenerateLevel()
{
	CMapGenerator MapGenerator;
	GameMap = MapGenerator.createNewLevel(DEFAULT_COUNT_OF_ROOM);
	_PathFinder->changeMap(GameMap);
	ActorsStack->setPathFinder(_PathFinder);
	ActorsStack->setPlayerPosition(GameMap->getStartPosition());
	ActorsStack->addMonster(GameMap);
}

bool CGame::startRender()
{
	if (Screen->initSDL())
		return true;
	return false;
}

void CGame::getPlayerInput()
{
	bool ExitFromLevel;
	GameLogic->playPlayer(ActorsStack, GameMap, &ExitFromLevel);
}

void CGame::renderGraphic()
{
	GameMap->updateVisibility(ActorsStack->getPlayerPosition());

	Screen->updateWindow(GameMap, ActorsStack);
}

void CGame::provideGameLogic()
{
	getPlayerInput();

	GameLogic->playMonstersTurn(ActorsStack, GameMap);
}

void CGame::startGameLoop()
{
	while (isRunning)
	{
		GameMap->printDebug();

		renderGraphic();

		provideGameLogic();
	}
}