#pragma once

#include "CMap.h"
#include "CPath.h"
#include "CRoomGenerator.h"
#include "../CRandomGenrator.h"

enum class TypeOfLabirithm
{
	HalfWallsAsPath = 0,
	PointInRoom = 1,
	AllWallsAsPath = 2
};

class CMapGenerator
{
private:

	const int CHANCE_OF_ADDTIONAL_PATH = 30;

	int CountOfRoomWhereCanEnter = 0;

	int SizeOfMap = 0;

	int IndexOfStartRoom;

	CMap* Map;

	CRandomGenrator Random;

public:
	CMap* createNewLevel(int RoomsCount);

private:

	CPosition getRandomPositionInRoom(CRoom* Room);

	void createRooms();

	void generateStartPosition();

	void generateExitFromLevel();

	bool canRoomBeNotReal(int IndexOfRoom);

	bool paintHalfWallsAsPath(CRoom* Room, std::vector<PathDirection> Directions);

	void paintPointInRoom(CRoom* Room, std::vector<PathDirection> Directions);

	void paintAllWallsAsPath(CRoom* Room);

	void moveRoomToIndexMap(CRoom* Room);

	void movePathToIndexMap(CPosition From, CPosition To, PathDirection Direction);

	void moveHorizontalPathToIndexMap(CPosition From, CPosition To, bool NeedAngle);

	void moveVerticalPathToIndexMap(CPosition From, CPosition To, bool NeedAngle);

	void createPathesBetweenRoom();

	void setPathesBeetwenRooms();

	void createMinimalPathes();

	void createAddtionalPathes();

	void feelLabirithm();

	void setupPath(CRoom* Room, PathDirection Direction);

	CPosition generateDoorPosition(CRoom* Room, PathDirection Direction);

	bool isAroundRoomNeedPath(PathDirection* Direction, CRoom* Room);

	CPosition getPositionOfRoomByIndex(int index);
};
