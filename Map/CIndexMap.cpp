#include "CIndexMap.h"

TypeOfCell CIndexMap::getTypeOfCell(CPosition Position)
{
	return isPositionInMap(Position) ? Map[Position.Y][Position.X].Type : TypeOfCell::Empty;
}

TypeOfCell CIndexMap::getCellForScreen(CPosition Position)
{
	if (isPositionInMap(Position) == false)
		TypeOfCell::Empty;  //TODO: Create Error

	if (Map[Position.Y][Position.X].HeroVision == true || Map[Position.Y][Position.X].Visible == true)
	{
		Map[Position.Y][Position.X].HeroVision = false;
		return Map[Position.Y][Position.X].Type;
	}

	TypeOfCell::Empty;
}

CPosition CIndexMap::getSize()
{
	return Size;
}

void CIndexMap::allocateMap(CPosition SizeOfMap)
{
	//Try - Catch
	Map = new SCell* [SizeOfMap.Y];
	for (int index = 0; index < SizeOfMap.Y; index++)
		Map[index] = new SCell[SizeOfMap.X];

	Size = SizeOfMap;
}

void CIndexMap::setCellVisible(CPosition Position)
{
	if (isPositionInMap(Position) == false)
		return; //TODO Crete Error

	Map[Position.Y][Position.X].Visible = true;
}

void CIndexMap::setHeroVision(CPosition Position)
{
	if (isPositionInMap(Position) == false)
		return; //TODO Crete Error

	Map[Position.Y][Position.X].HeroVision = true;
}

bool CIndexMap::isPositionInMap(CPosition Position)
{
	if (Position.X >= 0
		&& Position.X < Size.X
		&& Position.Y < Size.Y
		&& Position.Y >= 0)
		return true;
	return false;
}
