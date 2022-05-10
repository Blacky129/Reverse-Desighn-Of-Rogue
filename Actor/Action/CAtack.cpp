#include "CAtack.h"

CAtack::CAtack(CMovementOrAtack* Action, CActor* ToWhom, int Damage)
{
	WhoDoIt = Action->getWhoDoIt();
	From = Action->getStartOfMovement();
	To = Action->getDestination();
	Type = TypeOfAction::Atack;
	_ToWhom = ToWhom;
	_Damage = Damage;
}
