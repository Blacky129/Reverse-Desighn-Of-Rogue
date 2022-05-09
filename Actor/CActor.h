#pragma once

#include "../Map/CPosition.h"
#include "Controller/CController.h"

enum class TypeOfActor
{
	Rogue,
	Monster,
	Undefined
};

class CActor
{
protected:
	CPosition Position;

	int Health;
	
	int Level;
	
	bool Stuned;

	TypeOfActor Type;
public:
	CActor();

	void setActorPosition(CPosition NewPosition);

	CPosition getActorPosition();
private:
};

