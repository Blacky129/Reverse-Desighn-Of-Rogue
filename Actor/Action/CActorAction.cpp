#include "CActorAction.h"

CActorAction::CActorAction()
{
	WhoDoIt = nullptr;
	Type = TypeOfAction::None;
}

CActorAction::CActorAction(CActor* Actor, TypeOfAction ActionType)
{
	WhoDoIt = Actor;
	Type = ActionType;
}

void CActorAction::changeType(TypeOfAction NewType)
{
	Type = NewType;
}

TypeOfAction CActorAction::getType()
{
	return Type;
}

CActor* CActorAction::getWhoDoIt()
{
	return WhoDoIt;
}
