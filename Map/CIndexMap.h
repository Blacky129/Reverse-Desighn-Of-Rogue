#pragma once

#include "CPosition.h"

enum class TypeOfCell
{
	Empty = '.',
	Wall = 'W',
	Door = 'D',
	Path = 'P',
	Floor = 'F',
	Exit = 'E'
};

struct SCell
{
	TypeOfCell Type = TypeOfCell::Empty;
	bool Visible = false;
	bool HeroVision = false;
};

class CIndexMap
{
private:
	CPosition Size;

	SCell** Map;

	friend class CMapGenerator;

public:
	TypeOfCell getTypeOfCell(CPosition Position);

	TypeOfCell getCellForScreen(CPosition Position);

	CPosition getSize();

	void allocateMap(CPosition SizeOfMap);

	void setCellVisible(CPosition Position);

	void setHeroVision(CPosition Position);

private:
	bool isPositionInMap(CPosition Position);
};

