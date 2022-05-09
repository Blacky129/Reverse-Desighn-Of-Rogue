#include "CRoom.h"

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
