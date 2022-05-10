#include "CRoom.h"
#include "../CRandomGenrator.h"

TypeOfRoom CRoom::getTypeOfRoom()
{
	return Type;
}

CPosition CRoom::getTopLeftCornerPosition()
{
	return TopLeftCornerPosition;
}

CPosition CRoom::getSizeOfRoom()
{
	return SizeOfRoom;
}

bool CRoom::canPathTroughRoom()
{
	if (Type == TypeOfRoom::RealRoom || Type == TypeOfRoom::Labirithm)
		return true;

	return false;
}

bool CRoom::isNeedPath()
{
	for (int Direction = 0; Direction < 4; Direction++)
	{
		if (Pathes.at(Direction)->getStatus() == PathStatus::HasDoor)
			return false;
	}
	return true;
}

CPath* CRoom::getPath(PathDirection Direction)
{
	return Pathes.at(int(Direction));
}

bool CRoom::hasLight()
{
	return HasLight;
}

bool CRoom::isPositionInRoom(CPosition Position)
{
	if (
		Position.X >= TopLeftCornerPosition.X &&
		Position.X <= TopLeftCornerPosition.X + SizeOfRoom.X - 1 &&
		Position.Y >= TopLeftCornerPosition.Y &&
		Position.Y <= TopLeftCornerPosition.Y + SizeOfRoom.Y - 1
		)
		return true;
	return false;
}

CPosition CRoom::getRandomPositionInRoom()
{
	CRandomGenrator Generator;
	return CPosition{Generator.generateIntergerInRange(TopLeftCornerPosition.X + 1, TopLeftCornerPosition.X + SizeOfRoom.X - 2),
					 Generator.generateIntergerInRange(TopLeftCornerPosition.Y + 1, TopLeftCornerPosition.Y + SizeOfRoom.Y - 2)};
}

PathDirection getOppositeDirection(PathDirection Direction)
{
	switch (Direction)
	{
	case PathDirection::Up:
		return PathDirection::Down;

	case PathDirection::Down:
		return PathDirection::Up;
	
	case PathDirection::Left:
		return PathDirection::Right;
	
	case PathDirection::Right:
		return PathDirection::Left;
	}
}
