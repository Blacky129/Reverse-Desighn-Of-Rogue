#pragma once

#include "../Action/CActorAction.h"

class CActorAction;

class CController
{
protected:
	CActor* Owner;

public:
	CController(CActor* Actor)
	{
		Owner = Actor;
	}

	virtual CActorAction* actionActor() =0;
};

