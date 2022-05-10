#pragma once

#include "CPosition.h"
#include "CPath.h"
#include <vector>

enum class TypeOfRoom
{
	RealRoom,
	NoPathes,
	Labirithm,
	EndOfPath
};

enum class PathDirection
{
	Up = 0,
	Right = 1,
	Left = 3,
	Down = 2
};

PathDirection getOppositeDirection(PathDirection Direction);

class CRoom
{
public:
	TypeOfRoom getTypeOfRoom();

	CPosition getTopLeftCornerPosition();

	CPosition getSizeOfRoom();

	bool canPathTroughRoom();

	bool isNeedPath();

	CPath* getPath(PathDirection Direction);

	bool hasLight();

	bool isPositionInRoom(CPosition Position);

	CPosition getRandomPositionInRoom();
private:
	std::vector<CPath*> Pathes;

	TypeOfRoom Type;

	CPosition TopLeftCornerPosition;

	CPosition SizeOfRoom;

	bool HasLight;

	friend class CRoomGenerator;
};

