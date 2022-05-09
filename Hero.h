#pragma once
#include "Map/CPosition.h"

class CHero
{
private:

	int HP = 10;

	CPosition HeroPosition = {};

public:
	CHero();

	~CHero();

	void setHeroPosition(CPosition NewPosition);

	CPosition getHeroPosition();

	int getHeroHP();

	void updateHeroHP(int Modifier);

private:
};

