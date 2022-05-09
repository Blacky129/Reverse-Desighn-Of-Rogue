#include "Hero.h"

CHero::CHero()
{
}

CHero::~CHero()
{
}

void CHero::setHeroPosition(CPosition NewPosition)
{
	if (NewPosition.X >= 0 && NewPosition.Y >= 0)
		this->HeroPosition = NewPosition;
}

CPosition CHero::getHeroPosition()
{
	return this->HeroPosition;
}

int CHero::getHeroHP()
{
	return this->HP;
}

void CHero::updateHeroHP(int Modifier)
{
	this->HP += Modifier;
	if (this->HP < 0)
		this->HP = 0;
}
