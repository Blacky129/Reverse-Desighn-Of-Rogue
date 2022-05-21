#include "Game.h"
#include"Map/CMapGenerator.h"

#include <iostream> //TODO Delete
CGame::CGame()
{
	_ActorsStack = new CActorStack;
	_GameLogic = new CGameLogic;
	Screen = new CScreen;
	GameMap = nullptr;
	_PathFinder = new CPathFinder;
	isRunning = true;
}

void CGame::startGame()
{
	if (Screen->initSDL() == false)
		return;

	if (_ActorsStack->createPlayer(this) == false)
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

void CGame::onNotify(EVENT_TYPE Event)
{
	switch (Event)
	{
	case EVENT_TYPE::RERENDER_EVENT:
		renderGraphic();
	default:
		break;
	}
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
	_ActorsStack->setPathFinder(_PathFinder);
	_ActorsStack->setPlayerPosition(GameMap->getStartPosition());
	_ActorsStack->addMonster(GameMap);
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
	_GameLogic->playPlayer(_ActorsStack, GameMap, &ExitFromLevel);
}

void CGame::renderGraphic()
{
	GameMap->updateVisibility(_ActorsStack->getPlayerPosition());

	Screen->updateWindow(GameMap, _ActorsStack);
}

void CGame::provideGameLogic()
{
	getPlayerInput();

	_GameLogic->playMonstersTurn(_ActorsStack, GameMap);
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