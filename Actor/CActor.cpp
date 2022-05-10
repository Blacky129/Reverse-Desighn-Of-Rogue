#include "CActor.h"

CActor::CActor()
{
	Health = 0;
	Level = 1;
	Stuned = false;
	Type = TypeOfActor::Undefined;
}

void CActor::setActorPosition(CPosition NewPosition)
{
	if (NewPosition.X >= 0 && NewPosition.Y >= 0)
		Position = NewPosition;
}

CActorAction* CActor::playActor()
{
	return Controller->actionActor();
}

CPosition CActor::getActorPosition()
{
	return Position;
}
