#include "CMap.h"
#include "../CRandomGenrator.h"
#include <iostream>

CPosition CMap::getSizeOfMap()
{
	return IndexMap->getSize();
}

TypeOfCell CMap::getTypeOfCell(CPosition Position)
{
	return IndexMap->getTypeOfCell(Position);
}

void CMap::updateVisibility(CPosition HeroPosition)
{
	switch (IndexMap->getTypeOfCell(HeroPosition))
	{
	case TypeOfCell::Door:
	case TypeOfCell::Exit:
	case TypeOfCell::Floor:
		//update Visibility in Room
		updateVisibilityInRoom(HeroPosition);
	case TypeOfCell::Path:
		//update Visibility Around
		updateVisibilityHeroVision(HeroPosition);
		return;
	default:
		return;
	}
}

void CMap::updateVisibilityInRoom(CPosition HerpPosition)
{
	int IndexOfRoom = getIndexOfRoomByPosition(HerpPosition);

	CRoom* Room = RoomsOfLevel.at(IndexOfRoom);

	if (Room->hasLight() == false)
		return;

	for (int Y = Room->getTopLeftCornerPosition().Y; Y < Room->getTopLeftCornerPosition().Y + Room->getSizeOfRoom().Y; Y++)
	{
		for (int X = Room->getTopLeftCornerPosition().X; X < Room->getTopLeftCornerPosition().X + Room->getSizeOfRoom().X; X++)
			IndexMap->setCellVisible(CPosition{ X, Y });
	}

}

void CMap::updateVisibilityHeroVision(CPosition HeroPosition)
{
	std::vector<CPosition> Vision = { HeroPosition + CPosition{ +1, -1 },
									  HeroPosition + CPosition{ +1, +1 },
									  HeroPosition + CPosition{ -1, +1 },
									  HeroPosition + CPosition{ -1, -1 },
									  HeroPosition + CPosition{ +1, +0 },
									  HeroPosition + CPosition{ -1, +0 },
									  HeroPosition + CPosition{ +0, +1 },
									  HeroPosition + CPosition{ +0, -1 } };

	for (CPosition Position : Vision)
	{
		if (isInRoomWithoutLight(Position) == false)
			IndexMap->setCellVisible(Position);

		if (IndexMap->getTypeOfCell(Position) == TypeOfCell::Door || IndexMap->getTypeOfCell(Position) == TypeOfCell::Wall)
			IndexMap->setCellVisible(Position);

		IndexMap->setHeroVision(Position);
	}
}

bool CMap::isInRoomWithoutLight(CPosition Position)
{
	CRoom* Room;
	int IndexOfRoom;
	switch (IndexMap->getTypeOfCell(Position))
	{
	case TypeOfCell::Door:
	case TypeOfCell::Exit:
	case TypeOfCell::Floor:
	case TypeOfCell::Wall:
		IndexOfRoom = getIndexOfRoomByPosition(Position);
		Room = RoomsOfLevel.at(IndexOfRoom);
		if (Room->hasLight() == false)
			return true;
	default:
		return false;
	}
}

bool CMap::isRoomCorrectForSpawn(int IndexOfRoom, int IndexOfRoomWithRogue)
{
	if (IndexOfRoom == IndexOfRoomWithRogue)
		return false;

	if (RoomsOfLevel.at(IndexOfRoom)->getTypeOfRoom() != TypeOfRoom::RealRoom)
		return false;

	return true;
}

bool CMap::isRoomReal(int IndexOfRoom)
{
	if (IndexOfRoom < 0 || IndexOfRoom > RoomsOfLevel.size())
		exit(12);

	if (RoomsOfLevel.at(IndexOfRoom)->getTypeOfRoom() == TypeOfRoom::RealRoom)
		return true;
	else
		return false;
}

int CMap::getIndexOfRoomByPosition(CPosition Position)
{
	CPosition RoomPosition = {};
	RoomPosition.X = int(Position.X / 24);
	RoomPosition.Y = int(Position.Y / 8);
	return RoomPosition.X + RoomPosition.Y * 3;
}

void CMap::printDebug()
{
	for (int Y = 0; Y < IndexMap->getSize().Y; Y++)
	{
		for (int X = 0; X < IndexMap->getSize().X; X++)
		{
			std::cout << char(IndexMap->getTypeOfCell(CPosition{X, Y}));
		}
		std::cout << '\n';
	}

	std::cout << '\n';
}

CPosition CMap::getPositionForSpawn(CPosition RoguePosition)
{
	int IndexOfRoomWithRogue = -1;
	for (int indexOfRoom = 0; indexOfRoom < RoomsOfLevel.size(); indexOfRoom++)
	{
		if (RoomsOfLevel.at(indexOfRoom)->isPositionInRoom(RoguePosition))
		{
			IndexOfRoomWithRogue = indexOfRoom;
			break;
		}
	}

	int IndexOfRoom;
	CRandomGenrator  Generator;
	do
	{
		IndexOfRoom = Generator.generateIntergerInRange(0, 8);
	}while (isRoomCorrectForSpawn(IndexOfRoom, IndexOfRoomWithRogue) == false);

	return RoomsOfLevel.at(IndexOfRoom)->getRandomPositionInRoom();
}

TypeOfCell CMap::getCellForRender(CPosition Position)
{
	return IndexMap->getCellForScreen(Position);
}

CPosition CMap::getStartPosition()
{
	return StartPosition;
}

bool CMap::isExitFromLevel(CPosition Position)
{
	if (Position == ExitFromLevel)
		return true;
	return false;
}

bool CMap::isCanGoByDiagonal(CPosition From, CPosition To)
{
	CPosition Difference;
	Difference.Y = To.Y - From.Y;
	Difference.X = To.X - From.X;

	if (getTypeOfIteration(CPosition{ From.X + Difference.X, From.Y + Difference.Y }) == TypeIteration::None)
		return false;
	if (getTypeOfIteration(CPosition{ From.X , From.Y + Difference.Y }) == TypeIteration::None)
		return false;
	if (getTypeOfIteration(CPosition{ From.X + Difference.X, From.Y }) == TypeIteration::None)
		return false;

	return true;
}

TypeIteration CMap::getTypeOfIteration(CPosition Position)
{
	switch (IndexMap->getTypeOfCell(Position))
	{
	case TypeOfCell::Wall:
	case TypeOfCell::Empty:
		return TypeIteration::None;
	case TypeOfCell::Door:
	case TypeOfCell::Path:
	case TypeOfCell::Floor:
	case TypeOfCell::Exit:
		return TypeIteration::Move;
	}
}


