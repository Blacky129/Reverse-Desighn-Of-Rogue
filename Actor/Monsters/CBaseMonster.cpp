#include "CBaseMonster.h"

CBaseMonster::CBaseMonster()
{
	Controller = new CBaseAI(this);
	Type = TypeOfActor::Monster;
	_PathFinder = nullptr;
	_isActive = false;
}

void CBaseMonster::setGoal(CActor* NewGoal)
{
	_Goal = NewGoal;
}

CPosition CBaseMonster::getGoalPosition()
{
	if (_Goal != nullptr)
		return _Goal->getActorPosition();
	return CPosition{ -1, -1 };
}

CPathFinder* CBaseMonster::getPathFinder()
{
	return _PathFinder;
}

void CBaseMonster::activateMonster()
{
	_isActive = true;
}

bool CBaseMonster::getActive()
{
	return _isActive;
}

void CBaseMonster::setPathFinder(CPathFinder* PathFinder)
{
	if (_PathFinder == nullptr)
	{
		_PathFinder = PathFinder;
	}
}
