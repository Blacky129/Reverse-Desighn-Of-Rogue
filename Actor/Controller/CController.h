#pragma once

#include "../Action/CActorAction.h"

class CActorAction;

class CController
{
public:
	virtual CActorAction* actionActor() =0;
};

