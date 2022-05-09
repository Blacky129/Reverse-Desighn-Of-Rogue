#pragma once

class CActor;

#include "CActorAction.h"
#include "../../Map/CPosition.h"

class CMovementOrAtack : public CActorAction
{
protected:
	CPosition From;
	CPosition To;
public:
	CMovementOrAtack(CActorAction* Action, CPosition NewFrom, CPosition NewTo);

	CPosition getStartOfMovement();

	CPosition getDestination();

	CPosition getVectorOfMovement();
private:
};