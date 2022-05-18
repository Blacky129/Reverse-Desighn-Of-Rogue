#include "CGameLogic.h"
#include <iostream>

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

		delete Action;//TO DO History of Actions
	}while (CanEnd == false);
		
}

void CGameLogic::playMonstersTurn(CActorStack* ActorsStack, CMap* Map)
{
	bool LastMonster = false;
	while (LastMonster == false)
	{
		CActorAction* Action = ActorsStack->getMonsterAction(&LastMonster);

		if (Action->getType() == TypeOfAction::None)
			continue;

		if (canProvideAction(Action, Map))
			provideAction(Action, Map, nullptr, ActorsStack);

		delete Action;//TO DO History of Actions
	}
}

void CGameLogic::provideAction(CActorAction* Action, CMap* Map, bool* PlayerExit, CActorStack* ActorStack)
{
	switch (Action->getType())
	{
	case TypeOfAction::ExitFromLevel:
		if (PlayerExit != nullptr)
			*PlayerExit = true;
		return;
	case TypeOfAction::Movement:
		if (ActorStack->getActorInThisPosition(dynamic_cast<CMovementOrAtack*>(Action)->getDestination()))
			provideAtack(dynamic_cast<CMovementOrAtack*>(Action), ActorStack, dynamic_cast<CMovementOrAtack*>(Action)->getDestination());
		else
			provideMovement(dynamic_cast<CMovementOrAtack*>(Action));
		return;
	case TypeOfAction::None:
		return;
	}
}

void CGameLogic::provideAtack(CMovementOrAtack* Action, CActorStack* ActorStack, CPosition ZoneOfAtack)
{
	Action = new CAtack(Action, ActorStack->getActorInThisPosition(dynamic_cast<CMovementOrAtack*>(Action)->getDestination()), 0);

	std::cout << "Atacked";
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