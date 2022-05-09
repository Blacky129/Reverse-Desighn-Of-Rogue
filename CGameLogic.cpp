#include "CGameLogic.h"

void CGameLogic::playPlayer(CActorStack* ActorsStack, CMap* Map, bool* PlayerExitFromLevel)
{
	bool CanEnd = false;
	do 
	{
		CActorAction* Action = ActorsStack->getPlayerAction();

		if (Action->getType() == TypeOfAction::None)
			continue;

		CanEnd = canProvideAction(Action, Map);

		if (CanEnd)
			provideAction(Action, Map, PlayerExitFromLevel, ActorsStack);
	}while (CanEnd == false);
		
}

void CGameLogic::provideAction(CActorAction* Action, CMap* Map, bool* PlayerExit, CActorStack* ActorStack)
{
	switch (Action->getType())
	{
	case TypeOfAction::ExitFromLevel:
		*PlayerExit = true;
		return;
	case TypeOfAction::Movement:
		if (ActorStack->isAnyoneInPosition(dynamic_cast<CMovementOrAtack*>(Action)->getDestination()))
			provideAtack(dynamic_cast<CMovementOrAtack*>(Action), ActorStack);
		else
			provideMovement(dynamic_cast<CMovementOrAtack*>(Action));
		return;
	case TypeOfAction::None:
		return;
	}
}

void CGameLogic::provideAtack(CMovementOrAtack* Action, CActorStack* ActorStack)
{
	//TODO function
}

void CGameLogic::provideMovement(CMovementOrAtack* Action)
{
	CActor* Actor = Action->getWhoDoIt();
	Actor->setActorPosition(Action->getDestination());
}

bool CGameLogic::canProvideAction(CActorAction* Action, CMap* Map)
{
	switch (Action->getType())
	{
	case TypeOfAction::None:
		return true;
	case TypeOfAction::Movement:
		return canMove( dynamic_cast<CMovementOrAtack*>(Action), Map);
	case TypeOfAction::ExitFromLevel:
		return canExit(Action->getWhoDoIt(), Map);
	default:
		return false;
	}
}

bool CGameLogic::canExit(CActor* Actor, CMap* Map)
{
	return Map->isExitFromLevel(Actor->getActorPosition());
}

bool CGameLogic::canMove(CMovementOrAtack* Action, CMap* Map)
{
	if (Action->getVectorOfMovement().getVectorLength() > 1)
		return Map->isCanGoByDiagonal(Action->getStartOfMovement(), Action->getDestination());
	else
		return (Map->getTypeOfIteration(Action->getDestination()) == TypeIteration::Move);
}