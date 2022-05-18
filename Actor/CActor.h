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

	CController* Controller;

	int Health;
	
	int Level;
	
	bool Stuned;

	TypeOfActor Type;
public:
	CActor();
	virtual ~CActor()
	{
		delete Controller;
	}

	void setActorPosition(CPosition NewPosition);

	CActorAction* playActor();

	CPosition getActorPosition();
private:
};

