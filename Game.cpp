#include "Game.h"
#include"Map/CMapGenerator.h"

#include <iostream> //TODO For Debug

CGame::CGame()
{
	ActorsStack = new CActorStack;
	GameLogic = new CGameLogic;
	Screen = new CScreen;
	GameMap = nullptr;
	Player = new CHero;
	KeyboardInput = new CInputManager;
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

	//TODO Monster Creation

	startGameLoop();
}


CGame::~CGame()
{
	delete Screen;
	delete GameMap;
	delete Player;
	delete KeyboardInput;
}

bool isWindowsSizeOrPositionChanges(CPosition PrevWindowSize, CPosition NewWindowSize,
	CPosition PrevWindowPosition, CPosition NewWindowPosition)
{
	if (PrevWindowPosition == NewWindowPosition && PrevWindowSize == NewWindowSize)
		return false;
	return true;
}

void CGame::getInput()
{
	InputType Event;
	int PrevWindowsSizeX, PrevWindowsSizeY, NewWindowsSizeX, NewWindowsSizeY;//For Windows size
	int PrevWindowsPositionX, PrevWindowsPositionY, NewWindowsPosX, NewWindowsPosY;//For Windows Position
	
	SDL_GetWindowPosition(Screen->getWindow(), &PrevWindowsPositionX, &PrevWindowsPositionY);
	SDL_GetWindowSize(Screen->getWindow(), &PrevWindowsSizeX, &PrevWindowsSizeY);

	do
	{
		SDL_GetWindowSize(this->Screen->getWindow(), &NewWindowsSizeX, &NewWindowsSizeY);
		SDL_GetWindowPosition(this->Screen->getWindow(), &NewWindowsPosX, &NewWindowsPosY);
		
		Event = KeyboardInput->getInput();
		switch (Event)
		{
		case InputType::Quit:
			this->isRunning = false;
			return;

		case InputType::MovementDownLeft:
			if (GameMap->isCanGoByDiagonal(Player->getHeroPosition(), CPosition{ Player->getHeroPosition().X - 1, Player->getHeroPosition().Y + 1 }) == false)
				return;
			this->moveHero(Event);
			return;
		case InputType::MovementDownRight:
			if (GameMap->isCanGoByDiagonal(Player->getHeroPosition(), CPosition{ Player->getHeroPosition().X + 1, Player->getHeroPosition().Y + 1 }) == false)
				return;
			this->moveHero(Event);
			return;
		case InputType::MovementUpRight:
			if (GameMap->isCanGoByDiagonal(Player->getHeroPosition(), CPosition{ Player->getHeroPosition().X + 1, Player->getHeroPosition().Y - 1}) == false)
				return;
			this->moveHero(Event);
			return;
		case InputType::MovementUpLeft:
			if (GameMap->isCanGoByDiagonal(Player->getHeroPosition(), CPosition{ Player->getHeroPosition().X - 1, Player->getHeroPosition().Y - 1}) == false)
				return;
			this->moveHero(Event);
			return;

		case InputType::MovementUp:
		case InputType::MovementDown:
		case InputType::MovementRight:
		case InputType::MovementLeft:
			this->moveHero(Event);
			return;

		case InputType::ExitLevel:
			this->exitLevel();
		default:
			break;
		}

		CPosition PrevWindowSize = {PrevWindowsSizeX, PrevWindowsSizeY};
		CPosition PrevWindowPosition = {PrevWindowsPositionX, PrevWindowsPositionY};
		CPosition NewWindowSize = {NewWindowsSizeX, NewWindowsSizeY};
		CPosition NewWindowPosition = {NewWindowsPosX, NewWindowsPosY};

		if (isWindowsSizeOrPositionChanges(PrevWindowSize, NewWindowSize, PrevWindowPosition, NewWindowPosition))
			return;
	} while (Event == InputType::Null);
}

void CGame::exitLevel()
{
	if (GameMap->isExitFromLevel(this->Player->getHeroPosition()))
	{
		delete this->GameMap;
		this->GameMap = new CMap;
		this->GenerateLevel();
	}
}


void CGame::moveHero(InputType Direction)
{
	CPosition HeroPosition = this->Player->getHeroPosition();
	CPosition NewPosition = CPosition{-1,-1};
	switch (Direction)
	{
	case InputType::MovementUp:
		NewPosition = CPosition{ HeroPosition.X, HeroPosition.Y - 1 };
		break;
	case InputType::MovementDown:
		NewPosition = CPosition{ HeroPosition.X, HeroPosition.Y + 1 };
		break;
	case InputType::MovementRight:
		NewPosition = CPosition{ HeroPosition.X + 1, HeroPosition.Y };
		break;
	case InputType::MovementLeft:
		NewPosition = CPosition{ HeroPosition.X - 1, HeroPosition.Y };
		break;
	case InputType::MovementUpRight:
		NewPosition = CPosition{ HeroPosition.X + 1, HeroPosition.Y - 1};
		break;
	case InputType::MovementUpLeft:
		NewPosition = CPosition{ HeroPosition.X - 1, HeroPosition.Y - 1};
		break;
	case InputType::MovementDownRight:
		NewPosition = CPosition{ HeroPosition.X + 1, HeroPosition.Y + 1};
		break;
	case InputType::MovementDownLeft:
		NewPosition = CPosition{ HeroPosition.X - 1, HeroPosition.Y + 1};
		break;
	default:
		return;
	}
	
	switch (GameMap->getTypeOfIteration(NewPosition))
	{
	case TypeIteration::Move:
		Player->setHeroPosition(NewPosition);
		//GameMap->updateMapOfVisability(NewPosition);
		return;
	case TypeIteration::Atack:
		//TO DO

	case TypeIteration::None:
	default:
		return;
	}


}

void CGame::GenerateLevel()
{
	CMapGenerator MapGenerator;
	GameMap = MapGenerator.createNewLevel(DEFAULT_COUNT_OF_ROOM);
	ActorsStack->setPlayerPosition(GameMap->getStartPosition());
}

bool CGame::startRender()
{
	if (Screen->initSDL())
		return true;
	return false;
}

bool CGame::startInput()
{
	if (KeyboardInput->initInput())
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
}

void CGame::startGameLoop()
{
	while (isRunning)
	{
		GameMap->printDebug();

		renderGraphic();

		provideGameLogic();
		//getInput();

		//TODO Monster Turn
	}
}