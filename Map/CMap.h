#pragma once

#include "CRoom.h"
#include "CIndexMap.h"
#include <vector>

enum class TypeIteration
{
	None,
	Move,
	Atack
};

class CMap
{
private:

	CIndexMap* IndexMap;

	std::vector<CRoom*> RoomsOfLevel;

	CPosition StartPosition;

	CPosition ExitFromLevel;

	friend class CMapGenerator;

public:

	void printDebug();

	CPosition getPositionForSpawn(CPosition RoguePosition);

	TypeOfCell getCellForRender(CPosition Position);

	CPosition getStartPosition();

	bool isExitFromLevel(CPosition Position);

	bool isCanGoByDiagonal(CPosition From, CPosition To);

	TypeIteration getTypeOfIteration(CPosition Position);

	CPosition getSizeOfMap();

	TypeOfCell getTypeOfCell(CPosition Position);

	void updateVisibility(CPosition HeroPosition);

private:
	void updateVisibilityInRoom(CPosition HerpPosition);

	void updateVisibilityHeroVision(CPosition HeroPosition);

	bool isRoomReal(int IndexOfRoom);

	int getIndexOfRoomByPosition(CPosition Position);

	bool isInRoomWithoutLight(CPosition Position);

	bool isRoomCorrectForSpawn(int IndexOfRoom, int IndexOfRoomWithRogue);
};

