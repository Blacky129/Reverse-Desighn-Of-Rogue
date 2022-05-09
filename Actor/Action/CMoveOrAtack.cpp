#include "CMoveOrAtack.h"

CMovementOrAtack::CMovementOrAtack(CActorAction* Action, CPosition NewFrom, CPosition NewTo)
{
	WhoDoIt = Action->getWhoDoIt();
	Type = TypeOfAction::Movement;
	From = NewFrom;
	To = NewTo;
	delete Action;
}

CPosition CMovementOrAtack::getDestination()
{
	return To;
}

CPosition CMovementOrAtack::getVectorOfMovement()
{
	return To - From;
}
