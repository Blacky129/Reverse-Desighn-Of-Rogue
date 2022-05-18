#include "CMoveOrAtack.h"

CMovementOrAtack::CMovementOrAtack(CActor* NewWhoDoIt, CPosition NewFrom, CPosition NewTo)
{
	WhoDoIt = NewWhoDoIt;
	Type = TypeOfAction::Movement;
	From = NewFrom;
	To = NewTo;
}

CMovementOrAtack::CMovementOrAtack(CActorAction* Action, CPosition NewFrom, CPosition NewTo)
{
	WhoDoIt = Action->getWhoDoIt();
	Type = TypeOfAction::Movement;
	From = NewFrom;
	To = NewTo;
	delete Action;
}

CPosition CMovementOrAtack::getStartOfMovement()
{
	return From;
}

CPosition CMovementOrAtack::getDestination()
{
	return To;
}

CPosition CMovementOrAtack::getVectorOfMovement()
{
	return To - From;
}
