#include "CBaseMonster.h"

CBaseMonster::CBaseMonster()
{
	Controller = new CBaseAI(this);
	Type = TypeOfActor::Monster;
}
